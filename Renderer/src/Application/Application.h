#pragma once

#include "Consumer/Window.h"
#include "Consumer/Camera.h"
#include "Event/Event.h"
#include "Renderer/Renderer.h"
#include "Resources/Model/Model.h"

class Application
{

public:

	Application();

	void Run();
	

private:

	void OnUpdate();
	void OnEvent(Event&);

private:

	Model* CreateTriangle(float x, float y, float z);
	Model* Create3DCube(float x, float y, float z);

	void TestObject();

	Window* m_Window;
	bool m_Running = true;

	Renderer* m_Renderer;
	Camera* m_Camera;

	//Time Variables
	float m_Time = 0, p_Time = 0, n_Time = 0;
};

