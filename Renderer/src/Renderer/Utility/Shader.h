#pragma once
#include <glad/glad.h>
#include <iostream>
#include <unordered_map>

class Shader
{
public:

	Shader(std::string, std::string);
	
	inline GLuint GetID() { return m_ShaderID; }


private:

	std::string LoadShader(std::string path);
	void CreateShader(std::string, GLenum, GLuint&);
	void CreateShaderProg(GLuint, GLuint);

private:

	GLuint m_ShaderID = NULL;
	std::unordered_map<GLenum, std::string> shaderType;
};

