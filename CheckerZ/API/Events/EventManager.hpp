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

	enum class GameHistoryState
	{
		DO,
		UNDO,
		REDO,
		REPLAY
	};

	class EventManager final
	{
		public:
			std::deque<Movement> gameHistory;

			std::stack<Movement> undoStack;
			std::stack<Movement> redoStack;

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

			Movement handleState(Movement t_move, GameHistoryState t_historyState = GameHistoryState::DO);
		
		private:
			Movement manageUndo();
			Movement manageRedo();
			void manageReplay();

		private:
			EventManager() = delete;
			EventManager(const EventManager&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager operator=(const EventManager&) = delete;
			EventManager operator=(EventManager&&) = delete;
	};

} } }
#endif !EVENT_MANAGER_HPP