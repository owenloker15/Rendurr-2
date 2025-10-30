#pragma once

#include <memory>

#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"

namespace Rendurr {

	class Application {
	public:
		Application();
		~Application() = default;

		void run();

		template<std::derived_from<Layer> T, typename... Args>
		void pushLayer(Args&&... args)
		{
			m_layerStack.emplace_back(std::make_unique<T>(std::forward<Args>(args) ... ));
		}
		void pushOverlay(Layer* layer);

	private:
		void onEvent(Event& event);
		bool onWindowCloseEvent(WindowCloseEvent& event);

	private:
		static std::unique_ptr<Application> s_application;

		bool m_running = false;

		std::unique_ptr<Window> m_window;
		std::vector<std::unique_ptr<Layer>> m_layerStack;
		// LayerStack m_layerStack;
	};

} // namespace Rendurr
