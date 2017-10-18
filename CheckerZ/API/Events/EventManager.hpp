#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "EventFactory.hpp"

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

			// GAME STATE EVENTS
			inline void winGame() const
			{
				EventFactory::create(GameSystemState::WIN)->invoke();
			}

			inline void loseGame() const
			{
				EventFactory::create(GameSystemState::LOSE)->invoke();
			}

			inline void quitGame() const
			{
				EventFactory::create(GameSystemState::QUIT)->invoke();
			}

			// ENTITY STATE EVENTS
			inline void moveEntity(const std::shared_ptr<Entity::Entity> &t_entity, const vec2 &t_pos) const
			{
				EventFactory::create(GameplayState::MOVE)->invoke(t_entity, t_pos);
			}

			inline void takeEntityPawn(const std::shared_ptr<Entity::Entity> &t_entity) const
			{
				EventFactory::create(GameplayState::TAKE)->invoke(t_entity);
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