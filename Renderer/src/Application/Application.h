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

	Model* CreateTriangle();
	Model* Create3DCube();

	void TestObject();

	Window* m_Window;
	bool m_Running = true;

	Renderer* m_Renderer;
	Camera m_Camera;

};

