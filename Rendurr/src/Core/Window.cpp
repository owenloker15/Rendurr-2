#include "Window.hpp"

#include "Log.hpp"
#include "Events/Event.hpp"
#include "Events/EventPublisher.hpp"

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
		// Window/Application Events
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowCloseEvent event;
				EventPublisher::getInstance()->publish(event);
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowResizeEvent event((float)width, (float)height);
				EventPublisher::getInstance()->publish(event);
			});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos)
			{
				WindowMoveEvent event((float)xpos, (float)ypos);
				EventPublisher::getInstance()->publish(event);
			});

		// Mouse Events
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				MouseMoveEvent event((float)xPos, (float)yPos);
				EventPublisher::getInstance()->publish(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					MousePressEvent event(button);
					EventPublisher::getInstance()->publish(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleaseEvent event(button);
					EventPublisher::getInstance()->publish(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				MouseScrollEvent event((float)xOffset, (float)yOffset);
				EventPublisher::getInstance()->publish(event);
			});
	}
}
