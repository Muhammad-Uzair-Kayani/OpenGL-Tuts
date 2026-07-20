#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Utility/Shader.h"

class Renderer
{

public:

	Renderer();

	void OnUpdate(GLFWwindow* window);

private:

	void Render(GLFWwindow* window);
	void Draw();

private:
	std::vector<Shader> m_ShaderPrograms;
};

