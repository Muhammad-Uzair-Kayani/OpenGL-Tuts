#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Resources/Model/Model.h"

class Renderer
{

public:

	Renderer();

	void OnUpdate(GLFWwindow* window);
	inline void PushObject(Model* object) { if(object->GetSucces())m_Objects.push_back(object); }

private:

	void Draw(GLFWwindow* window);

private:
	
	std::vector<Model*> m_Objects;

};

