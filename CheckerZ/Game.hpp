#ifndef GAME_HPP
#define GAME_HPP

// project includes
#include "API/Board.hpp"
#include "API/Events/EventManager.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/AI/AI.hpp"

// std::includes
#include <memory>
#include <vector>
#include <utility>
#include <stack>
#include <queue>

namespace CheckerZ
{
	// the game creation class
	class Game final
	{
		enum class TurnState
		{
			FIRST,
			BEGIN,
			END
		};

		private:
			std::string m_title;

			// States
			API::Events::GameSystemState m_gameState;
			TurnState m_turnState;
			
			// Players
			std::shared_ptr<Entity::Entity> m_player1;
			std::shared_ptr<Entity::Entity> m_player2;

			// Board
			std::shared_ptr<API::Board> m_gameBoard;

			// Moves generator
			std::shared_ptr<API::Utils::MovesGenerator> m_moveGenerator;
	
			// game system/board handlers
			std::stack<API::Board::board<API::Pawn, API::Board::s_boardLen>> m_undoStack;
			std::stack<API::Board::board<API::Pawn, API::Board::s_boardLen>> m_redoStack;

		public:
			Game();
			~Game();
			
			inline bool getIsRunning() const { return m_gameState == API::Events::GameSystemState::RUN || m_gameState == API::Events::GameSystemState::WIN; }
			inline bool getNextTurn() const { return m_turnState == TurnState::END; }
			
			inline void setTitle(const std::string& t_title) { m_title = t_title; }

			void begin();
			void update();
			void draw();
			void end();
				
			// public helpers
			inline void clearDraw() { printTitle(); m_gameBoard->display(); }
			friend void readInput(Game& game, std::string& command, uint8& keyFrom, uint8& keyTo, uint32& valueFrom, uint32& valueTo);

		private:
			inline void setGameState(const API::Events::GameSystemState& t_newState) { m_gameState = t_newState; }
			inline void setTurnState(const TurnState& t_newState) { m_turnState = t_newState; }
			inline void printTitle() const { system("cls"); API::Utils::Logger::message(API::Utils::MessageType::INF, "\n\t\t\t", m_title); }
			
			void displayEntityData(std::shared_ptr<Entity::Entity>& t_entity);
			void initMovesGenerator(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator, std::shared_ptr<Entity::Entity>& t_entity);
			void swapEntityTurns(const std::shared_ptr<Entity::Entity>& t_entityOnTurn);
			void endTurn(const std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator);
			// Game helpers declaration
			// game state (e.g. undo/redo ...) helpers
			void undoHelper();
			void redoHelper();
			// timer helper
			void delayHelper(double t_maxDelayTime);

		private:
			Game(const Game&) = delete;
			Game(Game&&) = delete;
	};
}

#endif // !GAME_HPP