#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Renderer
{

public:

	void OnUpdate(GLFWwindow* window);

private:

	void Render(GLFWwindow* window);
	void Draw();
};

