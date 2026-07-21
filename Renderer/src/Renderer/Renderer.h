#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Resources/Model/Model.h"
#include "Consumer/Camera.h"

class Renderer
{

public:

	Renderer(Camera* camera);

	void OnUpdate(GLFWwindow* window);
	void PushObject(Model* object);

private:

	void Draw(GLFWwindow* window);

private:
	
	std::vector<Model*> m_Objects;
	Camera* s_CameraInstance;
};

