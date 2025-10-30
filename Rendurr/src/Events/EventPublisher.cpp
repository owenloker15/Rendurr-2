#include "EventPublisher.hpp"

namespace Rendurr
{
	EventPublisher* EventPublisher::getInstance()
	{
		static EventPublisher instance;
		return &instance;
	}

	void EventPublisher::publish(const Event& event) const
	{
		
		for (const auto& callbacks : m_callbacks)
	}
}
