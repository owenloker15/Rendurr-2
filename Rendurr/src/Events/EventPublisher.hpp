#pragma once
#include <functional>

#include "Event.hpp"

namespace Rendurr
{
	using FunctionCallback = std::function<void(const Event&)>;

	class EventPublisher
	{
	public:
		static EventPublisher* getInstance();

		void publish(const Event& event) const;

		template<std::derived_from<Event> T>
		void subscribe(FunctionCallback callback);
	private:
		EventPublisher() = default;

		EventPublisher(const EventPublisher&) = delete;
		EventPublisher& operator=(const EventPublisher&) = delete;

		static EventPublisher* s_instance;
	};
}
