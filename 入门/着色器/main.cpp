#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
#pragma endregion

#pragma region 渲染循环
	/*渲染循环*/
	// glfwWindowShouldClose用来检查window是否被要求退出
	while (!glfwWindowShouldClose(window)) {
		processInput(window); // 处理输入

		/*渲染操作*/
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// 用颜色清空屏幕
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// 用颜色清空屏幕
		glClear(GL_COLOR_BUFFER_BIT);// 清空一个缓冲位的缓冲（还不太理解）

		/*传入时间*/
		myShader.setFloat("time", glfwGetTime() * 2);

		/*绘制三角形*/
		glBindVertexArray(VAO);
		//glUseProgram(shaderProgram);
		myShader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);


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
}
