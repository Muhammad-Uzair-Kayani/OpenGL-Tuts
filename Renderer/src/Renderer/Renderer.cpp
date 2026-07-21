#include "Renderer.h"

Renderer::Renderer(Camera* camera) : s_CameraInstance(camera)
{

}

void Renderer::OnUpdate(GLFWwindow* window)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto object : m_Objects)
	{
		object->OnUpdate(s_CameraInstance->GetProjectionMatrix(), s_CameraInstance->GetViewMatrix());
	}
	Draw(window);
}

void Renderer::PushObject(Model* object)
{
	if (object->GetSucces())
		m_Objects.push_back(object);
	object->TransformObject(s_CameraInstance->GetProjectionMatrix(),
							s_CameraInstance->GetViewMatrix());
}

void Renderer::Draw(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}
