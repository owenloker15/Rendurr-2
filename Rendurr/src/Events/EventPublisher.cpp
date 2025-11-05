#include "EventPublisher.hpp"

#include "Core/Log.hpp"

namespace Rendurr
{
	EventPublisher* EventPublisher::getInstance()
	{
		static EventPublisher instance;
		return &instance;
	}

	void EventPublisher::publish(Event& event) const
	{
		// Early return if not callbacks were found for that event
		if (!m_callbacks.contains(event.getType()))
		{
			return;
		}

		for (const auto& callback: m_callbacks.at(event.getType()))
		{
			callback(event);
		}
	}
}
