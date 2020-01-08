//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//int fakeMain() {
//	glfwInit();// 初始化GLFW
//	/*glfwWindowHint用来配置GLFW，第一个参数是选项名，第二个参数是这个选项的值*/
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 将主版本号设为3（因为用的OpenGL版本是3.3）
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 将此版本号设为3
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// 使用核心模式
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);如果是MAC OS X系统需要加上这句
//
//	/*创建窗口对象*/
//	GLFWwindow* window = glfwCreateWindow(800, 600, "OpengGL_Testing", nullptr, nullptr);// 设置窗口大小、名字
//	if (window == nullptr) {
//		cout << "创建窗口失败" << endl;
//		glfwTerminate();// 销毁所有剩余的窗口和游标
//		return -1;
//	}
//	glfwMakeContextCurrent(window);// 设置当前的上下文（OpenGL是一个庞大的状态机，其状态被称为上下文）
//
//	/*使用GLAD管理指针*/
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "初始化GLAD失败" << endl;
//		return -1;
//	}
//
//	/*设置视口，告诉OpenGL渲染窗口的尺寸大小*/
//	glViewport(0, 0, 800, 600);// 前两个是窗口左下角的位置，后两个是宽和高
//
//	/*告诉GLFW，每次窗口调用的时候使用framebuffer_size_callback函数*/
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	/*渲染循环*/
//	// glfwWindowShouldClose用来检查window是否被要求退出
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window); // 处理输入
//
//		/*渲染操作*/
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// 用颜色清空屏幕
//		glClear(GL_COLOR_BUFFER_BIT);// 清空一个缓冲位的缓冲（还不太理解）
//
//		glfwSwapBuffers(window); // 交换颜色缓冲
//		glfwPollEvents(); // 检查有没有触发事件（比如键盘输入、鼠标移动等等），更新窗口状态，并调用对应的回调函数
//	}
//
//	/*释放资源*/
//	glfwTerminate();
//
//	return 0;
//}
//
//// 回调函数，窗口大小改变的时候也应该改变视口的大小
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	// 不知道这个window有什么作用
//	glViewport(0, 0, 800, 600);
//}
//
//// 处理输入
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)// 判断是否按下Esc
//		glfwSetWindowShouldClose(window, true);// 将窗口设置为需要关闭
//}
//
////int main() {
////	return fakeMain();
////}