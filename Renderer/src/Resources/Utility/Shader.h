#pragma once
#include <glad/glad.h>
#include <iostream>
#include <unordered_map>

class Shader
{
public:

	Shader(std::string, std::string);
	
	inline GLuint GetID() { return m_ShaderID; }
	inline void UseProgram() { glUseProgram(m_ShaderID); }
	inline GLuint GetTextureID(std::string name) { UseProgram(); return glGetUniformLocation(m_ShaderID, name.c_str()); }

private:

	std::string LoadShader(std::string path);
	void CreateShader(std::string, GLenum, GLuint&);
	void CreateShaderProg(GLuint, GLuint);

private:

	GLuint m_ShaderID = NULL;
	std::unordered_map<GLenum, std::string> shaderType;
};

