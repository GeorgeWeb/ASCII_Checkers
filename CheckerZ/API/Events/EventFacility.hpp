#ifndef EVENT_FACILIY_HPP
#define EVENT_FACILIY_HPP

// project includes
#include "../../Common.hpp"
#include "../../Entity/Entity.hpp"

// std::includes
#include <functional>
#include <memory>

namespace CheckerZ { namespace API { namespace Events {

	class EventFacility
	{
		public:
			explicit EventFacility() = default;
			virtual ~EventFacility() = default;

			// not all of the three overloads will require definition, but at least one will be need to be,
			// so I can choose for the type of event
			virtual void invoke() const { };
			virtual void invoke(std::shared_ptr<Entity::Entity> t_entity, const uint16 t_pawnIdx) const { };
			virtual void invoke(std::shared_ptr<Entity::Entity> t_entity, const uint16 t_pawnIdx, const vec2 &t_pos) const { };
		
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