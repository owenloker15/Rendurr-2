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
		uint32_t width;
		uint32_t height;
	};

	class Application {
	public:
		Application(const ApplicationSpecification& spec);
		~Application() = default;

		void run();
		void close();

		static Application& getInstance();

		template<std::derived_from<Layer> T, typename... Args>
		void pushLayer(Args&&... args)
		{
			auto pLayer = std::make_unique<T>(std::forward<Args>(args) ...);
			pLayer->onAttach();
			m_layerStack.emplace_back(std::move(pLayer));
		}

		std::shared_ptr<Window> getWindow() const;

		template<typename T>
		T* getNativeWindow() const
		{
			const auto nativeWindow = m_window->getNativeWindow();
			if (const auto castedWindow = static_cast<T*>(nativeWindow))
			{
				return castedWindow;
			}
			return nullptr;
		}

	private:
		bool onWindowCloseEvent(WindowCloseEvent& event);

	private:
		static Application* s_application;

		bool m_running = false;

		std::shared_ptr<Window> m_window;
		std::vector<std::unique_ptr<Layer>> m_layerStack;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime;
	};

} // namespace Rendurr
