#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Use(GLuint, GLuint) const;
	inline unsigned int GetID() const { return m_ProgID; };

	//Private utility functions for shader compilation and linking
private:

	const std::string LoadFromFile(const char* path);
	void CreateShader(const char* path, GLuint& shader, GLenum type);
	void CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);

	//Private member variable to store the shader program ID
private:
	unsigned int m_ProgID;
};

