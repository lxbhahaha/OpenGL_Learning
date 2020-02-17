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

#pragma region ����ͼ�����

	#pragma region ����

	// ͼ�εĶ�������
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

	#pragma endregion

	#pragma region �任����

	glm::mat4 model; // ģ�;���
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ��x����ת-55��
	glm::mat4 view; // �۲����
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // �������(0,0,3)���������෴�ƶ� Ϊ�ƶ�(0,0,-3)
	glm::mat4 projection; // ͶӰ����
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Fov��45�ȣ���Ļ�Ŀ�߱���800/600�����Ĳü��������0.1��Զ�����100

	#pragma endregion

	#pragma region EBO VAO VBO

	// EBO
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
	// ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ɫ
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	// ����UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	#pragma endregion

	#pragma region ��ͼ

	stbi_set_flip_vertically_on_load(true); // ��תY
	int width, height, nrChannels;
	unsigned char *data;
	// ��һ��ͼ
	unsigned int TexBuffer1;
	glGenTextures(1, &TexBuffer1);
	glActiveTexture(GL_TEXTURE0); // ����0�ŵ�Ԫ
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

	// �ڶ���ͼ
	unsigned int TexBuffer2;
	glGenTextures(1, &TexBuffer2);
	glActiveTexture(GL_TEXTURE1); // ����1�ŵ�Ԫ
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

	// ������Ȳ��� ZTEST
	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region ��Ⱦѭ��
	/*ָ����ͼ*/
	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	/*��Ⱦѭ��*/
	// glfwWindowShouldClose�������window�Ƿ�Ҫ���˳�
	while (!glfwWindowShouldClose(window)) {
		processInput(window); // ��������

		/*��Ⱦ����*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// ����ɫ�����Ļ
		glClear(GL_COLOR_BUFFER_BIT);// ���һ������λ�Ļ��壨����̫��⣩

		/*����������*/
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBuffer2);

		glBindVertexArray(VAO);
		myShader.use();
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/*Uniform*/
		myShader.setMat4("model", model);
		myShader.setMat4("view", view);
		myShader.setMat4("projection", projection);

		// ��ת
		model = glm::rotate(model, 0.002f * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glfwSwapBuffers(window); // ������ɫ����
		glfwPollEvents(); // �����û�д����¼�������������롢����ƶ��ȵȣ������´���״̬�������ö�Ӧ�Ļص�����

		// �����ɫ�������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
