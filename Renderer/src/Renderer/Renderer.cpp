#include "Renderer.h"

Renderer::Renderer()
{

}

void Renderer::OnUpdate(GLFWwindow* window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto object : m_Objects)
	{
		object->OnUpdate();
	}
	Draw(window);
}

void Renderer::Draw(GLFWwindow* window)
{
	for (auto object : m_Objects)
	{
		object->Draw();
	}
	glfwSwapBuffers(window);
}
