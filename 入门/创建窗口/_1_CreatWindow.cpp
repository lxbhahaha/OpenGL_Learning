//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//int fakeMain() {
//	glfwInit();// ��ʼ��GLFW
//	/*glfwWindowHint��������GLFW����һ��������ѡ�������ڶ������������ѡ���ֵ*/
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// �����汾����Ϊ3����Ϊ�õ�OpenGL�汾��3.3��
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// ���˰汾����Ϊ3
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ʹ�ú���ģʽ
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);�����MAC OS Xϵͳ��Ҫ�������
//
//	/*�������ڶ���*/
//	GLFWwindow* window = glfwCreateWindow(800, 600, "OpengGL_Testing", nullptr, nullptr);// ���ô��ڴ�С������
//	if (window == nullptr) {
//		cout << "��������ʧ��" << endl;
//		glfwTerminate();// ��������ʣ��Ĵ��ں��α�
//		return -1;
//	}
//	glfwMakeContextCurrent(window);// ���õ�ǰ�������ģ�OpenGL��һ���Ӵ��״̬������״̬����Ϊ�����ģ�
//
//	/*ʹ��GLAD����ָ��*/
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "��ʼ��GLADʧ��" << endl;
//		return -1;
//	}
//
//	/*�����ӿڣ�����OpenGL��Ⱦ���ڵĳߴ��С*/
//	glViewport(0, 0, 800, 600);// ǰ�����Ǵ������½ǵ�λ�ã��������ǿ�͸�
//
//	/*����GLFW��ÿ�δ��ڵ��õ�ʱ��ʹ��framebuffer_size_callback����*/
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	/*��Ⱦѭ��*/
//	// glfwWindowShouldClose�������window�Ƿ�Ҫ���˳�
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window); // ��������
//
//		/*��Ⱦ����*/
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// ����ɫ�����Ļ
//		glClear(GL_COLOR_BUFFER_BIT);// ���һ������λ�Ļ��壨����̫��⣩
//
//		glfwSwapBuffers(window); // ������ɫ����
//		glfwPollEvents(); // �����û�д����¼�������������롢����ƶ��ȵȣ������´���״̬�������ö�Ӧ�Ļص�����
//	}
//
//	/*�ͷ���Դ*/
//	glfwTerminate();
//
//	return 0;
//}
//
//// �ص����������ڴ�С�ı��ʱ��ҲӦ�øı��ӿڵĴ�С
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	// ��֪�����window��ʲô����
//	glViewport(0, 0, 800, 600);
//}
//
//// ��������
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)// �ж��Ƿ���Esc
//		glfwSetWindowShouldClose(window, true);// ����������Ϊ��Ҫ�ر�
//}
//
////int main() {
////	return fakeMain();
////}