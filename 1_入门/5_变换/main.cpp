#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float mixValue = 0;
float uvScale = 1;

int main() {
#pragma region 窗口创建以及初始化
	glfwInit();// 初始化GLFW
	/*glfwWindowHint用来配置GLFW，第一个参数是选项名，第二个参数是这个选项的值*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 将主版本号设为3（因为用的OpenGL版本是3.3）
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 将此版本号设为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// 使用核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);如果是MAC OS X系统需要加上这句

	/*创建窗口对象*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpengGL_Testing", nullptr, nullptr);// 设置窗口大小、名字
	if (window == nullptr) {
		cout << "创建窗口失败" << endl;
		glfwTerminate();// 销毁所有剩余的窗口和游标
		return -1;
	}
	glfwMakeContextCurrent(window);// 设置当前的上下文（OpenGL是一个庞大的状态机，其状态被称为上下文）

	/*使用GLAD管理指针*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "初始化GLAD失败" << endl;
		return -1;
	}

	/*设置视口，告诉OpenGL渲染窗口的尺寸大小*/
	glViewport(0, 0, 800, 600);// 前两个是窗口左下角的位置，后两个是宽和高

	/*告诉GLFW，每次窗口调用的时候使用framebuffer_size_callback函数*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion

#pragma region 绘制三角形相关

	// 三角形的顶点数据
	float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	0, 2, 3  // 第二个三角形
	};

	// EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 创建顶点数组对象VAO（Vertex Array Object）
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // 第一个参数是几个对象，如果是多个对象的时候可以在第二个参数传一个数组进去
	glBindVertexArray(VAO); // 绑定VAO

	// 创建顶点缓冲对象VBO（Vertex Buffer Object）
	unsigned int VBO;
	glGenBuffers(1, &VBO);// 第一个参数是几个对象，如果是多个对象的时候可以在第二个参数传一个数组进去
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定VBO

	// 将顶点数据绑定到GL_ARRAY_BUFFER上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 着色器
	Shader myShader("vertexShader.vert", "fragmentShader.frag");

	// VAO的设置
	// 顶点坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 顶点颜色
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 顶点UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// === 贴图 ===
	stbi_set_flip_vertically_on_load(true); // 反转Y
	int width, height, nrChannels;
	unsigned char *data;
	// 第一张图
	unsigned int TexBuffer1;
	glGenTextures(1, &TexBuffer1);
	glActiveTexture(GL_TEXTURE0); // 激活0号单元
	glBindTexture(GL_TEXTURE_2D, TexBuffer1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Load Texture failed." << endl;
	}
	stbi_image_free(data);
	// 第二张图
	unsigned int TexBuffer2;
	glGenTextures(1, &TexBuffer2);
	glActiveTexture(GL_TEXTURE1); // 激活1号单元
	glBindTexture(GL_TEXTURE_2D, TexBuffer2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	data = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Load Texture failed." << endl;
	}
	stbi_image_free(data);

#pragma endregion

#pragma region 变换
	glm::mat4 trans; // 变换矩阵
#pragma endregion


#pragma region 渲染循环
	/*指定贴图*/
	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	/*渲染循环*/
	// glfwWindowShouldClose用来检查window是否被要求退出
	while (!glfwWindowShouldClose(window)) {
		processInput(window); // 处理输入

		/*渲染操作*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// 用颜色清空屏幕
		glClear(GL_COLOR_BUFFER_BIT);// 清空一个缓冲位的缓冲（还不太理解）

		/*绘制三角形*/
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBuffer2);

		glBindVertexArray(VAO);
		myShader.use();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*Uniform*/
		myShader.setFloat("mixValue", mixValue);
		myShader.setFloat("uvScale", uvScale);
		myShader.setMat4("transform", trans);

		/*变换*/
		trans = glm::scale(trans, glm::vec3(1.0, 1.0, 1.0) * (glm::float32(1) + glm::float32((sin(glfwGetTime()*10)/10)/30))); // 缩放
		trans = glm::rotate(trans, glm::radians(0.3f), glm::vec3(0.0, 0.0, 1.0)); // 旋转

		glfwSwapBuffers(window); // 交换颜色缓冲
		glfwPollEvents(); // 检查有没有触发事件（比如键盘输入、鼠标移动等等），更新窗口状态，并调用对应的回调函数
	}
#pragma endregion

	/*释放资源*/
	glfwTerminate();

	return 0;
}

// 回调函数，窗口大小改变的时候也应该改变视口的大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// 不知道这个window有什么作用
	glViewport(0, 0, 800, 600);
}

// 处理输入
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)// 判断是否按下Esc
		glfwSetWindowShouldClose(window, true);// 将窗口设置为需要关闭

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mixValue += 0.002;
		if (mixValue > 1)
			mixValue = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mixValue -= 0.002;
		if (mixValue < 0)
			mixValue = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		uvScale -= 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		uvScale += 0.01;
	}
}
