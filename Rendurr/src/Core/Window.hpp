#pragma once

#include "Events/Event.hpp"

#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <string>

#include "Render/RenderContext.hpp"

namespace Rendurr
{
	struct WindowData
	{
		int width;
		int height;
		std::string title;
	};

	class Window
	{
	public:
		Window(const WindowData& windowData);
		~Window();

		void onUpdate();

	private:
		void setupEventCallbacks();
	private:
		GLFWwindow* m_window;
		WindowData m_data;

		std::unique_ptr<RenderContext> m_renderContext;
	};
}
