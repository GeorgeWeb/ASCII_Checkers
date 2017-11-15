#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

// project includes
#include "EventFactory.hpp"

// std::includes
#include <exception>
#include <stack>
#include <queue>
#include <deque>

namespace CheckerZ { namespace API { namespace Events {
	
	/* 
	* Single header class - Implemented as a Singleton
	* Used as an API for events creation and invoking/calling.
	*/
	class EventManager final
	{
		public:
			static EventManager& getInstance()
			{
				static EventManager theInstance{};
				return theInstance;
			}

			inline void winGame(GameSystemState& t_finalGameState, std::shared_ptr<Board>& t_board, const std::shared_ptr<Entity::Entity>& t_player) const
			{
				EventFactory::create(GameSystemState::WIN)->invoke(t_finalGameState, t_board, t_player);
			}

			inline void loadGame(std::vector<char>& t_buffer, const std::string& t_file = "") const
			{
				EventFactory::create(GameSystemState::LOAD)->invoke(t_buffer);
			}

			inline void saveGame(std::vector<char>& t_buffer, const std::string& t_file) const
			{
				EventFactory::create(GameSystemState::SAVE)->invoke(t_buffer, t_file);
			}

			inline void quitGame() const
			{
				EventFactory::create(GameSystemState::QUIT)->invoke();
			}

			// used for AI
			inline void entityPawnAction(std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<API::Utils::MovesGenerator>& moveGenerator)
			{
				EventFactory::create(GameSystemState::ACTION)->invoke(t_entity, moveGenerator);
			}

			// used for Player
			inline void entityPawnAction(std::shared_ptr<Entity::Entity>& t_entity, const Position& t_posFrom, const Position& t_posTo,
				std::shared_ptr<API::Utils::MovesGenerator>& moveGenerator)
			{
				EventFactory::create(GameSystemState::ACTION)->invoke(t_entity, t_posFrom, t_posTo, moveGenerator);
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