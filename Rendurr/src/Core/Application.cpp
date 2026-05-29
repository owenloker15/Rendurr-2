#include "Application.hpp"

#include "Events/EventPublisher.hpp"
#include "Log.hpp"
#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"
#include "UI/UiLayer.hpp"
#include "Utils/Timer.hpp"

namespace Rendurr
{
    Application* Application::s_application = nullptr;

    Application::Application(const ApplicationSpecification& spec)
    {
        s_application = this;

        Log::Init();

        // TODO fix this jankness
        WindowData windowData;
        windowData.width = spec.width;
        windowData.height = spec.height;
        windowData.title = spec.title;

        m_pWindow = std::make_shared<Window>(windowData);

        EventPublisher::getInstance()->subscribe<WindowCloseEvent>(
            this, &Application::onWindowCloseEvent);

        pushLayer<UiLayer>();

        Renderer::enableDebug();
        Renderer::enableDepthTesting();
    }

    void Application::run()
    {
        m_running = true;

        m_lastFrameTime = Rendurr::getTime();
        while (m_running) {
            auto currentTime = Rendurr::getTime();
            std::chrono::duration<float> dt = currentTime - m_lastFrameTime;
            m_lastFrameTime = currentTime;
            float dt_seconds = dt.count();

            for (const auto& layer : m_layerStack) {
                layer->onUpdate(dt_seconds);
            }

            UiLayer::startFrame();
            for (const auto& layer : m_layerStack) {
                layer->onUiRender();
            }
            UiLayer::endFrame();

            m_pWindow->onUpdate();
        }

        m_running = false;
    }

    void Application::close()
    {
        m_running = false;
    }

    Application& Application::getInstance()
    {
        return *s_application;
    }

    std::shared_ptr<Window> Application::getWindow() const
    {
        return m_pWindow;
    }

    bool Application::onWindowCloseEvent(WindowCloseEvent& event)
    {
        m_running = false;
        return true;
    }
} // namespace Rendurr
