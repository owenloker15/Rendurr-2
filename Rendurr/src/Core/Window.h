#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"

namespace Rendurr
{
    struct WindowSpec
    {
        const char* title;
        uint32_t width = 0;
        uint32_t height = 0;
    };

    struct Window
    {
        WindowSpec specification;
        GLFWwindow* glfwWindow;
    };

    Window window_create(WindowSpec specification);
    void window_destroy(const Window& window);
    void window_swap_buffers(const Window& window);
    void window_retrieve_events(const Window& window, Input& input);

    void poll_events();

} // namespace Rendurr
