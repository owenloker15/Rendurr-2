/*
#include "LayerStack.hpp"

namespace Rendurr
{
	LayerStack::~LayerStack()
	{
		for (const auto& layer : m_Layers) {
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(std::unique_ptr<Layer> layer)
	{
		layer->onAttach();
		m_Layers.insert(m_Layers.begin() + m_InsertIndex, std::move(layer));
		m_InsertIndex++;
	}

	void LayerStack::popLayer(std::unique_ptr<Layer> layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
		if(iter != m_Layers.begin() + m_InsertIndex)
		{
			layer->onDetach();
			m_Layers.erase(iter);
			m_InsertIndex--;
		}
	}

	void LayerStack::pushOverlay(std::unique_ptr<Layer> overlay)
	{
		overlay->onAttach();
		m_Layers.push_back(std::move(overlay));
	}

	void LayerStack::popOverlay(std::unique_ptr<Layer> overlay)
	{
		auto iter = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if(iter != m_Layers.end())
		{
			overlay->onDetach();
			m_Layers.erase(iter);
		}
		
	}
}
*/
