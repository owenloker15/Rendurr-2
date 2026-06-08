#include "Rendurr.h"

#include "Core/Log.h"
#include "GLFW/glfw3.h"

namespace Rendurr
{
    void init()
    {
        if (!glfwInit()) {
            RND_CORE_ERROR("Failed to initialize GLFW!");
            glfwTerminate();
        }
    }
} // namespace Rendurr
