#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

#pragma region ���ڴ����Լ���ʼ��
	glfwInit();// ��ʼ��GLFW
	/*glfwWindowHint��������GLFW����һ��������ѡ�������ڶ������������ѡ���ֵ*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// �����汾����Ϊ3����Ϊ�õ�OpenGL�汾��3.3��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// ���˰汾����Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ʹ�ú���ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);�����MAC OS Xϵͳ��Ҫ�������

	/*�������ڶ���*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpengGL_Testing", nullptr, nullptr);// ���ô��ڴ�С������
	if (window == nullptr) {
		cout << "��������ʧ��" << endl;
		glfwTerminate();// ��������ʣ��Ĵ��ں��α�
		return -1;
	}
	glfwMakeContextCurrent(window);// ���õ�ǰ�������ģ�OpenGL��һ���Ӵ��״̬������״̬����Ϊ�����ģ�

	/*ʹ��GLAD����ָ��*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "��ʼ��GLADʧ��" << endl;
		return -1;
	}

	/*�����ӿڣ�����OpenGL��Ⱦ���ڵĳߴ��С*/
	glViewport(0, 0, 800, 600);// ǰ�����Ǵ������½ǵ�λ�ã��������ǿ�͸�

	/*����GLFW��ÿ�δ��ڵ��õ�ʱ��ʹ��framebuffer_size_callback����*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion

#pragma region �������������

	// �����εĶ�������
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	// ���������������VAO��Vertex Array Object��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // ��һ�������Ǽ�����������Ƕ�������ʱ������ڵڶ���������һ�������ȥ
	glBindVertexArray(VAO); // ��VAO

	// �������㻺�����VBO��Vertex Buffer Object��
	unsigned int VBO;
	glGenBuffers(1, &VBO);// ��һ�������Ǽ�����������Ƕ�������ʱ������ڵڶ���������һ�������ȥ
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��VBO

	// ���������ݰ󶨵�GL_ARRAY_BUFFER��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��ɫ��
	Shader myShader("vertexShader.vert", "fragmentShader.frag");

	// VAO������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
#pragma endregion

#pragma region ��Ⱦѭ��
	/*��Ⱦѭ��*/
	// glfwWindowShouldClose�������window�Ƿ�Ҫ���˳�
	while (!glfwWindowShouldClose(window)) {
		processInput(window); // ��������

		/*��Ⱦ����*/
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// ����ɫ�����Ļ
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// ����ɫ�����Ļ
		glClear(GL_COLOR_BUFFER_BIT);// ���һ������λ�Ļ��壨����̫��⣩

		/*����ʱ��*/
		myShader.setFloat("time", glfwGetTime() * 2);

		/*����������*/
		glBindVertexArray(VAO);
		//glUseProgram(shaderProgram);
		myShader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window); // ������ɫ����
		glfwPollEvents(); // �����û�д����¼�������������롢����ƶ��ȵȣ������´���״̬�������ö�Ӧ�Ļص�����
	}
#pragma endregion

	/*�ͷ���Դ*/
	glfwTerminate();

	return 0;
}

// �ص����������ڴ�С�ı��ʱ��ҲӦ�øı��ӿڵĴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// ��֪�����window��ʲô����
	glViewport(0, 0, 800, 600);
}

// ��������
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)// �ж��Ƿ���Esc
		glfwSetWindowShouldClose(window, true);// ����������Ϊ��Ҫ�ر�
}
