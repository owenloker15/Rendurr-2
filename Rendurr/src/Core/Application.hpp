#pragma once

#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"

#include <memory>
#include <chrono>

namespace Rendurr {

	struct ApplicationSpecification
	{
		std::string title;
		double width;
		double height;
	};

	class Application {
	public:
		Application(const ApplicationSpecification& spec);
		~Application() = default;

		void run();

		template<std::derived_from<Layer> T, typename... Args>
		void pushLayer(Args&&... args)
		{
			m_layerStack.emplace_back(std::make_unique<T>(std::forward<Args>(args) ... ));
		}

	private:
		bool onWindowCloseEvent(WindowCloseEvent& event);

	private:
		static std::unique_ptr<Application> s_application;

		bool m_running = false;

		std::unique_ptr<Window> m_window;
		std::vector<std::unique_ptr<Layer>> m_layerStack;
		// LayerStack m_layerStack;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime;
	};

} // namespace Rendurr
