#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

// project includes
#include "EventFactory.hpp"

// std::includes
#include <exception>

namespace CheckerZ { namespace API { namespace Events {
	
	/* 
	* Single header class - Implemented as a Singleton
	* Used as an API for events creation and invoking/calling.
	*/

	class EventManager final
	{
		public:
			static EventManager &getInstance()
			{
				static EventManager theInstance{};
				return theInstance;
			}

			inline void winGame() const
			{
				EventFactory::create(GameSystemState::WIN)->invoke();
			}

			inline void quitGame() const
			{
				EventFactory::create(GameSystemState::QUIT)->invoke();
			}

			inline void entityPawnAction(std::shared_ptr<Entity::Entity> t_entity, const Position& t_posFrom, Position&& t_posTo, 
				std::shared_ptr<API::Utils::MovesGenerator> moveGenerator)
			{
				EventFactory::create(GameSystemState::ACTION)->invoke(t_entity, t_posFrom, std::move(t_posTo), moveGenerator);
			}

		private:
			EventManager() = delete;
			EventManager(const EventManager&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager operator=(const EventManager&) = delete;
			EventManager operator=(EventManager&&) = delete;
	};

} } }
#endif !EVENT_MANAGER_HPP