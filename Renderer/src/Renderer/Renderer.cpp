#include "Renderer.h"

void Renderer::OnUpdate(GLFWwindow* window)
{
	Draw();
	Render(window);
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
