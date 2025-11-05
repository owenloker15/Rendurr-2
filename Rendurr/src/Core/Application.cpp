#include "Application.hpp"

#include "Log.hpp"
#include "Events/EventPublisher.hpp"
#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"
#include "Utils/Timer.hpp"

namespace Rendurr {
	Application::Application()
	{
		Log::Init();

		WindowData windowData;
		windowData.width = 800;
		windowData.height = 600;
		windowData.title = "Rendurr Engine";

		m_window = std::make_unique<Window>(windowData);

		//EventPublisher::getInstance()->subscribe<WindowCloseEvent>([this](WindowCloseEvent& e) {onWindowCloseEvent(e); });
		EventPublisher::getInstance()->subscribe<WindowCloseEvent>(this, &Application::onWindowCloseEvent);
	}

	void Application::run() {
		m_running = true;
		Renderer::enableDebugOutput();

		m_lastFrameTime = Rendurr::getTime();
		while (m_running) {
			auto currentTime = Rendurr::getTime();
			std::chrono::duration<float> dt = currentTime - m_lastFrameTime;
			m_lastFrameTime = currentTime;
			float dt_seconds = dt.count();

			Renderer::setClearColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			Renderer::clear();

			for (const auto& layer : m_layerStack)
			{
				layer->onUpdate(dt_seconds);
			}

			m_window->onUpdate();
		}

		m_running = false;
	}

	/*
	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
	}
	*/

	bool Application::onWindowCloseEvent(WindowCloseEvent& event)
	{
		m_running = false;
		return true;
	}
} // namespace Rendurr
