#pragma once

#include "Consumer/Window.h"
#include "Consumer/Camera.h"
#include "Event/Event.h"
#include "Renderer/Renderer.h"

class Application
{

public:

	Application();

	void Run();
	

private:

	void OnUpdate();
	void OnEvent(Event&);

private:

	Window* m_Window;
	bool m_Running = true;

	Renderer m_Renderer;
	Camera m_Camera;

};

