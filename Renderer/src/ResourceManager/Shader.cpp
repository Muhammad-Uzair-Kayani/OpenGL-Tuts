#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	GLuint vertexShader, fragmentShader;
	CreateShader(vertexPath, vertexShader, GL_VERTEX_SHADER);
	CreateShader(fragmentPath, fragmentShader, GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgID);
}

void Shader::Use() const
{
	glUseProgram(m_ProgID);
}

const std::string Shader::LoadFromFile(const char* path)
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
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << path << e.what() <<"\n";
	}

	return "";
}

void Shader::CreateShader(const char* path, GLuint& shader, GLenum type)
{
	const std::string source = LoadFromFile(path);
	const char* shaderSource = source.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::cout << "FAILED TO COMPILE THE SHADER SOURCE::OPENGL MESSAGE::";
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cout << log << "\n";
		return;
	}

	std::cout << "SUCCESS IN CREATING SHADER\n";
}

void Shader::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	m_ProgID = glCreateProgram();
	glAttachShader(m_ProgID, vertexShader);
	glAttachShader(m_ProgID, fragmentShader);
	glLinkProgram(m_ProgID);

	int success;
	char log[512];
	glGetProgramiv(m_ProgID, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "FAILED TO LINK THE SHADERS::OPENGL MESSAGE::";
		glGetProgramInfoLog(m_ProgID, 512, NULL, log);
		std::cout << log << "\n";
		return;
	}

	std::cout << "SUCCESS IN CREATING SHADER PROGRAM\n";
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
