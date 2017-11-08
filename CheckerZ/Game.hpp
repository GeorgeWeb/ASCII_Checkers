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

			// moves holder for undo
			std::stack<Movement> m_undo;
			// moves holder for redo
			std::stack<Movement> m_redo;
			// moves holder for saved game
			std::queue<Movement> m_save;

		public:
			Game();
			~Game();
			
			inline bool getIsRunning() const { return m_gameState == API::Events::GameSystemState::RUN 
												   || m_gameState == API::Events::GameSystemState::WIN; }
			inline bool getNextTurn() const { return m_turnState == TurnState::END; }
			
			inline void setTitle(const std::string& t_title) { m_title = t_title; }

			void begin();
			void update();
			void draw();
			void end();
				
		private:
			inline void setGameState(const API::Events::GameSystemState& t_newState) { m_gameState = t_newState; }
			inline void setTurnState(const TurnState& t_newState) { m_turnState = t_newState; }
			inline void printTitle() const { system("cls"); API::Utils::Logger::message(API::Utils::MessageType::INF, "\n\t\t\t", m_title); }
			inline void clearDraw() const { printTitle(); m_gameBoard->display(); }
			
			void displayEntityData(std::shared_ptr<Entity::Entity> t_entity);
			void initMovesGenerator(std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator, std::shared_ptr<Entity::Entity> t_entity);
			void swapEntityTurns(const std::shared_ptr<Entity::Entity>& t_entityOnTurn);

		private:
			Game(const Game&) = delete;
			Game(Game&&) = delete;
	};
}

#endif // !GAME_HPP