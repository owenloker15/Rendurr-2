#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <string>

#include "Events/Event.hpp"
#include "Render/RenderContext.hpp"

namespace Rendurr
{
    struct WindowData
    {
        uint32_t width = 0;
        uint32_t height = 0;
        std::string title;
    };

    class Window
    {
    public:
        Window(const WindowData& windowData);
        ~Window();

        uint32_t getWidth() const;
        uint32_t getHeight() const;

        void onUpdate();

        GLFWwindow* getNativeWindow() const;

    private:
        void setupEventCallbacks();

    private:
        GLFWwindow* m_window;
        WindowData m_data;

        std::unique_ptr<RenderContext> m_renderContext;
    };
} // namespace Rendurr
