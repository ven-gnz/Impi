#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math/Vector3.h>

class Shader
{
public:
	unsigned int ID = 0;
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	bool loadShaders(std::string vertexShaderFileName, std::string framentShaderFileName, std::string geometryPath);
	void use();
	void cleanup();
	void setM4_Uniform(const std::string& name, glm::mat4 m);
	bool getuniformLocation(std::string uniformName);
	void setUniformValue(int value);

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 mat) const;
	void setVec3(const std::string& name, glm::vec3 vec) const;
	void setVec3(const std::string& name, Impi::Vector3 v) const;

	void setVec3(const std::string& name, float a, float b, float c) const;
	void setVec2(const std::string& name, glm::vec2 vec) const;
	
	

private:
	GLuint mShaderProgram = 0;
	GLint mUniformLocation = -1;
	GLuint readShader(const std::string shaderFileName, GLuint shaderType);
};