#pragma once

#include "Core/Input.hpp"

#include <string>

namespace Rendurr
{
	class Event
	{
	public:
		virtual ~Event() = default;

		virtual std::string toString() const = 0;

		bool handled = false;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		std::string toString() const override
		{
			return "WindowCloseEvent";
		}

	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(float width, float height) : m_width(width), m_height(height) {}

		std::string toString() const override
		{
			return "WindowResizeEvent-> Width: " + std::to_string(m_width) + ", Height: " + std::to_string(m_height);
		}

		void setWidth(float width) { m_width = width; }
		float getWidth() const { return m_width; }

		void setHeight(float height) { m_height = height; }
		float getHeight() const { return m_height; }

	private:
		float m_width;
		float m_height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(float xPos, float yPos) : m_xPos(xPos), m_yPos(yPos) {}

		std::string toString() const override
		{
			return "WindowMoveEvent-> X-Position: " + std::to_string(m_xPos) + ", Y-Position: " + std::to_string(m_yPos);
		}

		void setXPos(float xPos) { m_xPos = xPos; }
		float getXPos() const { return m_xPos; }

		void setYPos(float xPos) { m_yPos = xPos; }
		float getYPos() const { return m_yPos; }

	private:
		float m_xPos;
		float m_yPos;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float xPos, float yPos) : m_xPos(xPos), m_yPos(yPos) {}

		std::string toString() const override
		{
			return "MouseMoveEvent-> X-Position: " + std::to_string(m_xPos) + ", Y-Position: " + std::to_string(m_yPos);
		}

		void setXPos(float xPos) { m_xPos = xPos; }
		float getXPos() const { return m_xPos; }

		void setYPos(float yPos) { m_yPos = yPos; }
		float getYPos() const { return m_yPos; }

	private:
		float m_xPos;
		float m_yPos;
	};

	class MousePressEvent : public Event
	{
	public:
		MousePressEvent(MouseCode button) : m_button(button) {}

		std::string toString() const override
		{
			return "MousePressEvent";
		}

		void setButton(MouseCode button) { m_button = button; }
		MouseCode getButton() const { return m_button; }

	private:
		MouseCode m_button;
	};

	class MouseReleaseEvent : public Event
	{
	public:
		MouseReleaseEvent(MouseCode button) : m_button(button) {}

		std::string toString() const override
		{
			return "MouseReleaseEvent";
		}

		void setButton(MouseCode button) { m_button = button; }
		MouseCode getButton() const { return m_button; }

	private:
		MouseCode m_button;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		std::string toString() const override
		{
			return "MouseScrollEvent-> X-Offset: " + std::to_string(m_xOffset) + ", Y-Offset: " + std::to_string(m_yOffset);
		}

		void setXOffset(float xOffset) { m_xOffset = xOffset; }
		float getXOffset() const { return m_xOffset; }

		void setYOffset(float yOffset) { m_yOffset = yOffset; }
		float getYOffset() const { return m_yOffset; }

	private:
		float m_xOffset;
		float m_yOffset;
	};


	class EventNotifier
	{
	public:
		EventNotifier(Event& event) : m_event(event) {}

		template<typename T, typename F>
		bool Notify(const F& func)
		{
			if (m_event.handled)
				return false;

			if (auto* newEvent = dynamic_cast<T*>(&m_event))
			{
				m_event.handled |= func(*newEvent);
				return true;
			}
			return false;

		}
	private:
		Event& m_event;
	};
}
