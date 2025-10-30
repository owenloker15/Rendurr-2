#pragma once

#include "Events/Event.hpp"

namespace Rendurr
{
	
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_Name(name) {}
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}

		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}
		virtual void onUiRender() {}

	private:
		std::string m_Name;
	};
}
