#pragma once

#include <functional>
#include <GLFW/glfw3.h>
#include "Event/Event.h"
#include "KeyStates.h"

class Input
{
public:

	static void Init(std::function<void(Event&)>, GLFWwindow*);
	static void OnUpdate();

private:

	static void OnWindowClose(GLFWwindow*);
	static void OnWindowResize(GLFWwindow*, int, int);
	// Mouse moved
	static void OnMouseMoved(GLFWwindow* window, double xpos, double ypos);
	// Mouse wheel scrolled
	static void OnMouseScrolled(GLFWwindow* window, double xoffset, double yoffset);
	// Mouse button pressed/released
	static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	static std::function<void(Event&)> Fn;
};

