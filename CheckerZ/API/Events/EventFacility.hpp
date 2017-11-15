#ifndef EVENT_FACILIY_HPP
#define EVENT_FACILIY_HPP

// project includes
#include "../../Common.hpp"
#include "../../Entity/Entity.hpp"

// std::includes
#include <functional>
#include <memory>

namespace CheckerZ { namespace API { namespace Events {

	// forward declare it here but will be defined in 'events.h'
	enum class GameSystemState;

	class EventFacility
	{
		public:
			explicit EventFacility() = default;
			virtual ~EventFacility() = default;

			// used for general system events
			virtual void invoke() const { };
			// used for win game event
			virtual void invoke(GameSystemState& t_finalGameState, std::shared_ptr<Board>& t_board) const { };
			// used for loading/saving a game
			virtual void invoke(std::vector<char>& t_buffer, const std::string& t_file = "") const { };
			// used for AI
			virtual void invoke(std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<API::Utils::MovesGenerator>& moveGenerator) { };
			// used for player
			virtual void invoke(std::shared_ptr<Entity::Entity>& t_entity, const Position& t_posFrom, const Position& t_posTo,
				std::shared_ptr<API::Utils::MovesGenerator>& moveGenerator) { };
		
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