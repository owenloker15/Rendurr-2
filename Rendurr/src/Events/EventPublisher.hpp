#pragma once
#include <functional>

#include "Event.hpp"

namespace Rendurr
{
	using FunctionCallback = std::function<void(Event&)>;

	class EventPublisher
	{
	public:
		static EventPublisher* getInstance();

		void publish(Event& event) const;

		template<typename EventType, typename T, typename EventTypeParam>
		requires std::is_same_v<EventType, EventTypeParam>
		void subscribe(T* obj, bool (T::*callback)(EventTypeParam&))
		{
			auto wrapperCallback = [obj, callback](Event& e)
			{
				if (EventType* derivedEvent = dynamic_cast<EventType*>(&e))
				{
					(obj->*callback)(*derivedEvent);
				}
			};
			m_callbacks[EventType::getStaticType()].push_back(wrapperCallback);
		}

		template<std::derived_from<Event> T>
		void subscribe(std::function<void(T&)> callback)
		{
			auto wrapperCallback = [callback](Event& e)
			{
				if (T* derivedEvent = dynamic_cast<T*>(&e))
				{
					callback(*derivedEvent);
				}
			};
			m_callbacks[T::getStaticType()].push_back(wrapperCallback);
		}
	private:
		EventPublisher() = default;

		EventPublisher(const EventPublisher&) = delete;
		EventPublisher& operator=(const EventPublisher&) = delete;

		std::unordered_map<std::string, std::vector<FunctionCallback>> m_callbacks;
	};
}
