#ifndef EVENT_FACILIY_HPP
#define EVENT_FACILIY_HPP

#include "../../Common.hpp"

// std::includes
#include <functional>
#include <memory>

namespace CheckerZ { namespace API { namespace Events {

	// TODO: CREATE A CMake ASAP !!!

	class EventFacility
	{
		public:
			explicit EventFacility() = default;
			virtual ~EventFacility() = default;

			virtual void invoke(const std::function<void()>& t_changeTitle = nullptr) const
			{
				std::invoke(t_changeTitle);
			}
		
		protected:
			virtual void initialize() = 0;
		
		private:
			EventFacility(const EventFacility&) = delete;
			EventFacility(EventFacility&&) = delete;
	};

	using Event = std::shared_ptr<EventFacility>;

} } }

#endif !EVENT_FACILIY_HPP