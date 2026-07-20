#pragma once

enum class EventType
{
	None = 0,
	KeyPressedEvent,
	MouseMovedEvent,
	MouseScrolledEvent,
	WindowResizeEvent,
	WindowClosedEvent
};

class Event
{
public:
	virtual ~Event() = default;

	EventType GetType() const { return m_Type; }

protected:
	EventType m_Type = EventType::None;
};

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(int key, int scancode, int action, int mods)
		: m_Key(key), m_ScanCode(scancode), m_Action(action), m_Mods(mods)
	{
		m_Type = EventType::KeyPressedEvent;
	}

	int GetKey() const { return m_Key; }
	int GetScanCode() const { return m_ScanCode; }
	int GetAction() const { return m_Action; }
	int GetMods() const { return m_Mods; }

private:
	int m_Key;
	int m_ScanCode;
	int m_Action;
	int m_Mods;
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(double x, double y)
		: m_X(x), m_Y(y)
	{
		m_Type = EventType::MouseMovedEvent;
	}

	double GetX() const { return m_X; }
	double GetY() const { return m_Y; }

private:
	double m_X;
	double m_Y;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(double xOffset, double yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset)
	{
		m_Type = EventType::MouseScrolledEvent;
	}

	double GetXOffset() const { return m_XOffset; }
	double GetYOffset() const { return m_YOffset; }

private:
	double m_XOffset;
	double m_YOffset;
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int height)
		: m_Width(width), m_Height(height)
	{
		m_Type = EventType::WindowResizeEvent;
	}

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

private:
	int m_Width;
	int m_Height;
};

class WindowClosedEvent : public Event
{
public:
    WindowClosedEvent()
    {
        m_Type = EventType::WindowClosedEvent;
    }
};