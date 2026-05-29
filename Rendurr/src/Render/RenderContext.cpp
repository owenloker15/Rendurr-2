#include "RenderContext.hpp"

#include <glad/glad.h>

#include "Core/Log.hpp"

namespace Rendurr
{
    RenderContext::RenderContext(GLFWwindow* window) : m_window(window) {}

    void RenderContext::init()
    {
        glfwMakeContextCurrent(m_window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            RND_CORE_ERROR("Failed to initialize glad!");
        }
    }

    void RenderContext::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

} // namespace Rendurr
