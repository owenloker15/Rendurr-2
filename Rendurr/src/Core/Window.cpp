#include "Window.hpp"

#include "Log.hpp"
#include "Events/Event.hpp"

namespace Rendurr
{
	Window::Window(const WindowData& windowData) : m_data(windowData)
	{
		if (!glfwInit())
		{
			RND_CORE_ERROR("Failed to initialize GLFW!");
		}

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		m_window = glfwCreateWindow(m_data.width, m_data.height, windowData.title.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			RND_CORE_ERROR("Failed to create window!");
			glfwTerminate();
		}

		m_renderContext = std::make_unique<RenderContext>(m_window);
		m_renderContext->init();

		setupEventCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::onUpdate()
	{
		m_renderContext->swapBuffers();

		glfwPollEvents();
	}

	void Window::setupEventCallbacks()
	{
		glfwSetWindowUserPointer(m_window, &m_data);

		// Window/Application Events
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.callback(event);
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowResizeEvent event((float)width, (float)height);

				data.callback(event);
			});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowMoveEvent event((float)xpos, (float)ypos);

				data.callback(event);
			});

		// Mouse Events
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMoveEvent event((float)xPos, (float)yPos);

				data.callback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MousePressEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleaseEvent event(button);
					data.callback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xOffset, (float)yOffset);
				data.callback(event);
			});
	}
}
