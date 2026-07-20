#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

struct WindowProp
{
	unsigned int Width = 0, Heigth = 0;
	std::string Title = "";
	GLFWwindow* m_Window;
	
	WindowProp(unsigned int Width, unsigned int Heigth,
				std::string Title)
	{
		m_Window = glfwCreateWindow(Width, Heigth, Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
	}
};


class Window
{

public:

	Window(unsigned int width = 1600, unsigned int height = 1000, std::string title = "Renderer");

	void WindowResize(int width, int height);
	inline GLFWwindow* GetWindow() { return m_Prop->m_Window; }

private:
	
	WindowProp* m_Prop;

};

