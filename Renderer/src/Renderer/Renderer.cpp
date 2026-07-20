#include "Renderer.h"

Renderer::Renderer()
{
	m_ShaderPrograms.push_back(Shader("src/Resources/Shaders/VertexShader.txt",
									  "src/Resources/Shaders/VertexShader.txt"));
}

void Renderer::OnUpdate(GLFWwindow* window)
{
	Render(window);
	Draw();
}

void Renderer::Render(GLFWwindow* window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void Renderer::Draw()
{

}
