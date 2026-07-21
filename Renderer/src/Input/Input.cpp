#include "Input.h"

void Input::OnWindowClose(GLFWwindow*)
{
	WindowClosedEvent e;
	Fn(e);
}

void Input::OnWindowResize(GLFWwindow* win, int width, int height)
{
	WindowResizeEvent e(width, height);
}

void Input::OnMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	MouseMovedEvent e(xpos, ypos);
	Fn(e);
}

void Input::OnMouseScrolled(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseScrolledEvent e(xoffset, yoffset);
	Fn(e);
}

void Input::OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (action == GLFW_PRESS)
		Key::m_Keys[key] = true;
	else if (action == GLFW_RELEASE)
		Key::m_Keys[key] = false;

	KeyPressedEvent e(key, scancode, action, mods);
	Fn(e);
}

void Input::OnUpdate()
{
	glfwPollEvents();
}

std::function<void(Event&)> Input::Fn;

void Input::Init(std::function<void(Event&)> eventFn, GLFWwindow* window)
{
	Fn = eventFn;
	glfwSetWindowCloseCallback(window, OnWindowClose);
	// Window resize
	glfwSetWindowSizeCallback(window, OnWindowResize);
	// Key pressed/released
	glfwSetKeyCallback(window, OnKeyPressed);
	// Mouse moved
	glfwSetCursorPosCallback(window, OnMouseMoved);
	// Mouse wheel scrolled
	glfwSetScrollCallback(window, OnMouseScrolled);
}


