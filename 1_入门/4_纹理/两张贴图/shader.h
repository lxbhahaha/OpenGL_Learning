#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	// 着色器程序ID
	unsigned int id;
	
	// 构造函数
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// 使用/激活函数
	void use();
	// uniform工具函数
	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value)const;
};