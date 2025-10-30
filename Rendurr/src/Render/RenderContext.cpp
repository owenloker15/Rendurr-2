#include "RenderContext.hpp"

#include "Core/Log.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	RenderContext::RenderContext(GLFWwindow* window) : m_window(window) {}

	void RenderContext::init()
	{
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			RND_CORE_ERROR("Failed to initialize glad!");
		}
	}

	void RenderContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

}
