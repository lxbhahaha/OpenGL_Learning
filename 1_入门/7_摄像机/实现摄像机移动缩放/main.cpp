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

#pragma region 函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
#pragma endregion

#pragma region 全局变量

/*摄像机*/
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // 摄像机位置
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // 摄像机的前方向
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  // 摄像机的上方向
glm::vec3 direction; // 方向
float pitch = 0; // 俯仰角度
float yaw = -90; // 偏航角
bool firstMouse = true; // 是否第一次进入
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45; // 视野

/*DeltaTime*/
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

#pragma endregion

// 主函数
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
	/*鼠标回调函数*/
	glfwSetCursorPosCallback(window, mouse_callback);
	/*鼠标滚轮回调函数*/
	glfwSetScrollCallback(window, scroll_callback);

#pragma endregion

#pragma region 绘制图形相关

	#pragma region 数据

	// 图形的顶点数据
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// 立方体位置
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	#pragma endregion

	#pragma region 变换矩阵

	glm::mat4 model; // 模型矩阵
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 在x上旋转-55度
	//glm::mat4 view; // 观察矩阵
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // 摄像机在(0,0,3)，即物体相反移动 为移动(0,0,-3)
	glm::mat4 projection; // 投影矩阵
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Fov是45度，屏幕的宽高比是800/600，近的裁剪面距离是0.1，远面距离100
	//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	#pragma endregion

	#pragma region EBO VAO VBO

	// EBO
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 顶点颜色
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	// 顶点UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	#pragma endregion

	#pragma region 贴图

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

	// 开启深度测试 ZTEST
	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region 摄像机
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // 摄像头的位置
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); //摄像头要看向的目标位置
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // 通过目标位置和自身位置计算出方向的单位向量
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // 定义世界坐标的上方向
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // 上方向和摄像头前方向叉乘得摄像头右方向
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // 摄像头右方向和摄像头前方向叉乘得摄像头上方向

	// LookAt 矩阵
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

#pragma endregion

#pragma region 渲染循环
	/*指定贴图*/
	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏鼠标, 不让鼠标离开窗口

	/*渲染循环*/
	// glfwWindowShouldClose用来检查window是否被要求退出
	while (!glfwWindowShouldClose(window)) {
		processInput(window); // 处理输入

		/*渲染操作*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// 用颜色清空屏幕
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色缓存和深度缓存

		/*绑定贴图*/
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBuffer2);

		/*绑定VAO*/
		glBindVertexArray(VAO);
		myShader.use();

		/*计算deltatime*/
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/*设置方块位置*/
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*Uniform*/
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // 改变观察矩阵
		myShader.setMat4("view", view);
		projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

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

// 处理键盘输入
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)// 判断是否按下Esc
		glfwSetWindowShouldClose(window, true);// 将窗口设置为需要关闭

	// 摄像头移动
	float cameraSpeed = 10.0f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
}

// 处理鼠标输入
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// 鼠标滚轮回调
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 110.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 110.0f)
		fov = 110.0f;
}