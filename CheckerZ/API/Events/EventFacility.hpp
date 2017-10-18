#ifndef EVENT_FACILIY_HPP
#define EVENT_FACILIY_HPP

#include "../../Common.hpp"
#include "../../Entity/Entity.hpp"

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

			// templated body prototype
			virtual void invoke() const { };
			virtual void invoke(std::shared_ptr<Entity::Entity> t_entity) const { };
			virtual void invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2 &t_pos) const { };
		
		protected:
			virtual void initialize() = 0;
		
		private:
			EventFacility(const EventFacility&) = delete;
			EventFacility(EventFacility&&) = delete;
	};

	// used for parameter passing with clearer typename
	using Event = std::shared_ptr<EventFacility>;

} } }

#endif !EVENT_FACILIY_HPP