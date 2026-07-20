#include "Window.h"

Window::Window(unsigned int width /*= 1600*/, unsigned int height /*= 1000*/, std::string title /*= "Renderer"*/)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Prop = new WindowProp(width, height, title);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, (int)width, (int)height);
}

void Window::WindowResize(int width, int height)
{
	glViewport(0, 0, (int)width, (int)height);
}


