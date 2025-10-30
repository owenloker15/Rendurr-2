/*
#pragma once

#include <memory>

#include "Layer.hpp"

#include <vector>

namespace Rendurr
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void pushLayer(std::unique_ptr<Layer> layer);
		void popLayer(std::unique_ptr<Layer> layer);
		void pushOverlay(std::unique_ptr<Layer> layer);
		void popOverlay(std::unique_ptr<Layer> layer);

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<std::unique_ptr<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::const_iterator end() const { return m_Layers.end(); }
		std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<std::unique_ptr<Layer>> m_Layers;
		unsigned int m_InsertIndex = 0;
	};
}
*/
