#include "Application.hpp"

#include <glad/glad.h>

#include "Log.hpp"
#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"

namespace Rendurr {
	Application::Application()
	{
		Log::Init();

		WindowData windowData;
		windowData.width = 800;
		windowData.height = 600;
		windowData.title = "Rendurr Engine";
		windowData.callback = [this](Event& e)
			{
				onEvent(e);
			};

		m_window = std::make_unique<Window>(windowData);
	}

	void Application::run() {
		m_running = true;
		Renderer::enableDebugOutput();

		while (m_running) {
			Renderer::setClearColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			Renderer::clear();

			for (const auto& layer : m_layerStack)
			{
				layer->onUpdate();
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

	void Application::onEvent(Event& event)
	{
		EventNotifier notifier(event);
		notifier.Notify<WindowCloseEvent>([this](WindowCloseEvent& e) {	return onWindowCloseEvent(e); });
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& event)
	{
		m_running = false;
		return true;
	}
} // namespace Rendurr
