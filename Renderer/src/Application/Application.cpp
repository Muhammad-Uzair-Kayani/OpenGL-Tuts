#include "Application.h"
#include "Input/Input.h"

#include "Resources/Model/Model.h"
#include "Resources/Shapes/Shape.h"
#include "Resources/Shapes/SolarSystem.h"
#include "Renderer/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input/KeyStates.h"

Application::Application()
{
	Key::Init();
	m_Window = new Window();
	m_Camera = new Camera(m_Window->GetWidth(), m_Window->GetHeight());
	Input::Init(std::bind(&Application::OnEvent, this, std::placeholders::_1), m_Window->GetWindow());
	m_Renderer = new Renderer(m_Camera);
	TestObject();
}

void Application::Run()
{

	while (m_Running)
	{
		n_Time = glfwGetTime();
		m_Time = n_Time - p_Time;

		OnSolarSystemUpdate(m_Time);
		OnUpdate();

		p_Time = n_Time;
	}
	
}

void Application::OnUpdate()
{
	Input::OnUpdate();
	m_Renderer->OnUpdate(m_Window->GetWindow());
	m_Camera->OnUpdate(m_Time);
}

void Application::OnEvent(Event& e)
{
	if (Key::m_Keys[GLFW_KEY_ESCAPE])
	{
		m_Running = false;
		return;
	}
	switch (e.GetType())
	{
	case (EventType::WindowClosedEvent):
	{
		m_Running = false;
		break;
	}
	case EventType::KeyPressedEvent:
	{
		KeyPressedEvent& w_Event = static_cast<KeyPressedEvent&>(e);
		m_Camera->PushKey(w_Event.GetKey());
		break;
	}
	case EventType::MouseMovedEvent:
	{
		MouseMovedEvent& w_Event = static_cast<MouseMovedEvent&>(e);
		m_Camera->OnMouseMove(w_Event.GetX(), w_Event.GetY(), m_Time);
		break;
	}
	case EventType::MouseScrolledEvent:
	{
		MouseScrolledEvent& w_Event = static_cast<MouseScrolledEvent&>(e);
		m_Camera->OnMouseScroll(w_Event.GetXOffset(), w_Event.GetYOffset(), m_Time);
		break;
	}
	case EventType::WindowResizeEvent:
	{
		WindowResizeEvent& w_Event = static_cast<WindowResizeEvent&>(e);
		m_Window->WindowResize(w_Event.GetWidth(), w_Event.GetHeight());
		break;
	}
	default:
		break;
	}	
	
}

void Application::TestObject()
{
	m_Renderer->PushObject(CreateSun());
	m_Renderer->PushObject(CreateMercury());
	m_Renderer->PushObject(CreateVenus());
	m_Renderer->PushObject(CreateEarth());
	m_Renderer->PushObject(CreateMoon());
	m_Renderer->PushObject(CreateMars());
	m_Renderer->PushObject(CreateJupiter());
	m_Renderer->PushObject(CreateSaturn());
	m_Renderer->PushObject(CreateSaturnRing());
	m_Renderer->PushObject(CreateUranus());
	m_Renderer->PushObject(CreateUranusRing());
	m_Renderer->PushObject(CreateNeptune());
	m_Renderer->PushObject(CreatePluto());
}
