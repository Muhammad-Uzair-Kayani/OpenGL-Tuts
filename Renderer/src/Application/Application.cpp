#include "Application.h"
#include "Input/Input.h"

Application::Application()
{
	m_Window = new Window();
	Input::Init(std::bind(&Application::OnEvent, this, std::placeholders::_1), m_Window->GetWindow());
}

void Application::Run()
{
	while (m_Running)
	{
		OnUpdate();
		m_Renderer.OnUpdate(m_Window->GetWindow());
	}
}

void Application::OnUpdate()
{
	Input::OnUpdate();
}

void Application::OnEvent(Event& e)
{
	switch (e.GetType())
	{
	case EventType::WindowClosedEvent:
	{
		m_Running = false;
		break;
	}
	case EventType::KeyPressedEvent:
	{
		KeyPressedEvent& w_Event = static_cast<KeyPressedEvent&>(e);
		m_Camera.OnKeyPressed(w_Event.GetKey(), w_Event.GetScanCode(),
								w_Event.GetAction(), w_Event.GetMods());
		break;
	}
	case EventType::MouseMovedEvent:
	{
		MouseMovedEvent& w_Event = static_cast<MouseMovedEvent&>(e);
		m_Camera.OnMouseMove(w_Event.GetX(), w_Event.GetY());
		break;
	}
	case EventType::MouseScrolledEvent:
	{
		MouseScrolledEvent& w_Event = static_cast<MouseScrolledEvent&>(e);
		m_Camera.OnMouseScroll(w_Event.GetXOffset(), w_Event.GetYOffset());
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
