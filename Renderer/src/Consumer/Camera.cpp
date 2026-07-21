#include "Camera.h"
#include <iostream>
#include "Input/KeyStates.h"

Camera::Camera(float width, float height) : 
		m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Width(width), m_Height(height)
{

	m_Projection = glm::perspective(glm::radians(45.0f), (float)width /
		(float)height, 0.1f, 100.0f);
	m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f));
	p_XPos = width / 2.f;
	p_YPos = height / 2.f;
}

void Camera::OnUpdate(float deltaTime)
{
	OnKeyPressed(deltaTime);
}

void Camera::OnMouseMove(double X, double Y, float deltaTime)
{
	std::cout << "FrameTime: " << deltaTime << " - Mouse Moved: " << X << ", " << Y << "\n";

	if (m_FirstMouse)
	{
		p_XPos = static_cast<float>(X);
		p_YPos = static_cast<float>(Y);
		m_FirstMouse = false;
	}

	n_XPos = static_cast<float>(X);
	n_YPos = static_cast<float>(Y);

	m_XPos = (n_XPos - p_XPos);
	m_YPos = (n_YPos - p_YPos);

	m_Yaw += m_XPos * m_Sensi * deltaTime;
	m_Pitch -= m_YPos * m_Sensi * deltaTime;

	// Clamp pitch...
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_CameraFront = glm::normalize(direction);

	m_View = glm::lookAt(
		m_CameraPosition,
		m_CameraPosition + m_CameraFront,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	p_XPos = n_XPos;
	p_YPos = n_YPos;
}

void Camera::OnMouseScroll(double X, double Y, float deltaTime)
{
	std::cout << "FrameTime: " << deltaTime << " - Mouse Scrolled: " << X << ", " << Y << "\n";

	m_FOV -= static_cast<float>(Y);

	if (m_FOV < 1.0f)
		m_FOV = 1.0f;
	if (m_FOV > 75.0f)
		m_FOV = 75.0f;

	m_Projection = glm::perspective(
		glm::radians(m_FOV),
		m_Width / m_Height,
		0.1f,
		100.0f
	);
	
}

void Camera::OnKeyPressed(float deltaTime)
{
	float movement = speed * deltaTime;
	glm::vec3 cameraUp(0.f, 1.f, 0.f);

	if (Key::m_Keys[GLFW_KEY_W])
		m_CameraPosition += movement * m_CameraFront;

	if (Key::m_Keys[GLFW_KEY_S])
		m_CameraPosition -= movement * m_CameraFront;

	if (Key::m_Keys[GLFW_KEY_A])
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, cameraUp)) * movement;

	if (Key::m_Keys[GLFW_KEY_D])
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, cameraUp)) * movement;

	m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront,
		glm::vec3(0.0f, 1.0f, 0.0f));
}

