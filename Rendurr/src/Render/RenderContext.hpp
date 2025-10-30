#pragma once

#include <GLFW/glfw3.h>

namespace Rendurr
{
	class RenderContext
	{
	public:
		RenderContext(GLFWwindow* window);

		void init();
		void swapBuffers();
	private:
		GLFWwindow* m_window;
	};
}
