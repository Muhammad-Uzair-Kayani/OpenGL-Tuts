#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexPath, std::string fragPath)
{
	shaderType[GL_VERTEX_SHADER] = "VERTEX SHADER";
	shaderType[GL_FRAGMENT_SHADER] = "FRAGMENT SHADER";
	GLuint vertex, fragment;
	CreateShader(vertexPath, GL_VERTEX_SHADER, vertex);
	CreateShader(fragPath, GL_FRAGMENT_SHADER, fragment);
	CreateShaderProg(vertex, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::LoadShader(std::string path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << path << e.what() << "\n";
	}

	return "";

}


void Shader::CreateShader(std::string path, GLenum type, GLuint& shaderID)
{
	std::string _source = LoadShader(path);
	const char* source = _source.c_str();
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	int status;
	char log[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, log);
		std::cout << "FAILED TO COMPILE " << shaderType[type] << " GL LOG INFO::";
		std::cout << log << "\n";
	}

	std::cout << "SUCCESSFULLY COMPILED " << shaderType[type] << "\n";
}


void Shader::CreateShaderProg(GLuint vertexID, GLuint fragID)
{
	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertexID);
	glAttachShader(m_ShaderID, fragID);
	glLinkProgram(m_ShaderID);


	int status;
	char log[512];
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(m_ShaderID, 512, NULL, log);
		std::cout << "FAILED TO LINK SHADERS::SHADER PROGRA GL LOG INFO::";
		std::cout << log << "\n";
	}

	std::cout << "SUCCESSFULLY LINKED SHADERS IN SHADER PROGRAM " << "\n";
}