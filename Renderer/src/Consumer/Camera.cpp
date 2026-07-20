#include "Camera.h"
#include <iostream>

void Camera::OnMouseMove(double X, double Y)
{
	std::cout << "Mouse Moved: " << X << ", " << Y << "\n";
}

void Camera::OnMouseScroll(double X, double Y)
{
	std::cout << "Mouse Scrolled: " << X << ", " << Y << "\n";
}

void Camera::OnKeyPressed(int key, int scancode, int action, int mods)
{
	char c = static_cast<char>(key);
	std::cout << "Button Pressed: " << c << "\n";
}

