#include "KeyStates.h"
#include <GLFW/glfw3.h>


std::unordered_map<int, bool> Key::m_Keys;


void Key::Init()
{
	Key::m_Keys[GLFW_KEY_W] = false;
	Key::m_Keys[GLFW_KEY_A] = false;
	Key::m_Keys[GLFW_KEY_S] = false;
	Key::m_Keys[GLFW_KEY_D] = false;
	Key::m_Keys[GLFW_KEY_ESCAPE] = false;
}
