#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <queue>

class Camera
{
public:

	Camera(float width, float height);

	inline glm::mat4 GetProjectionMatrix() { return m_Projection; }
	inline glm::mat4 GetViewMatrix() { return m_View; }

	void OnUpdate(float deltaTime);

	void OnMouseMove(double X, double Y, float deltaTime);
	void OnMouseScroll(double X, double Y, float deltaTime);
	void PushKey(int key) { m_KeyBuffer.push(key); }

private:

	void OnKeyPressed(float deltaTime);

private:

	std::queue<int> m_KeyBuffer;

	//Mouse Pos Track
	float m_XPos = 0, m_YPos = 0;
	float p_XPos = 0, p_YPos = 0;
	float n_XPos = 0, n_YPos = 0;
	bool m_FirstMouse = true;
	float m_Sensi = 80.f;
	float m_Pitch = 0.f, m_Yaw = -90.f;

	//Zoom Vars
	float m_Width, m_Height;
	float m_FOV = 45.f;

	//Movement Related
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	float speed = 1.f;

	//Transformation of World & Objects
	glm::mat4 m_View;
	glm::mat4 m_Projection;

};

