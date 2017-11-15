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

// AI speed defines
constexpr double SLOW = 5.0;
constexpr double NORMAL = 3.0;
constexpr double FAST = 1.0;
constexpr double LIGHTNING = 0.1;

namespace CheckerZ
{
	enum PlayerType
	{
		HUMAN		= 0,
		EASY_CPU	= 1,
		MEDIUM_CPU	= 2,
		HARD_CPU	= 3
	};

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
			std::shared_ptr<Entity::Entity> m_redPlayer; ///> always first
			std::shared_ptr<Entity::Entity> m_blackPlayer;

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
			inline const std::shared_ptr<API::Board>& getGameBoard() { return m_gameBoard; }
			inline void setTitle(const std::string& t_title) { m_title = t_title; }

			// player info setters
			void setRedPlayer(PlayerType t_playerType, double t_speed = 0.0, const std::string& t_name = "");
			void setBlackPlayer(PlayerType t_playerType, double t_speed = 0.0, const std::string& t_name = "");

			void begin();
			void update();
			void draw();
			void end();
			
			// -------------- //
			// public helpers //
			// -------------- //
			inline void clearDraw() { printTitle(); m_gameBoard->display(); }
			// friend helper functions
			// reads the command input from the player to play the game or change the game state
			friend void readInput(Game& t_game, std::string& t_command, uint8& t_keyFrom, uint8& t_keyTo, uint32& t_valueFrom, uint32& t_valueTo);
			// loads game data from a save file into the current game object
			friend void loadGame(Game &t_game);
			// saves the current game's data into a file
			friend void saveGame(Game& t_game);

		private:
			inline void setGameState(const API::Events::GameSystemState& t_newState) { m_gameState = t_newState; }
			inline void setTurnState(const TurnState& t_newState) { m_turnState = t_newState; }
			inline void printTitle() const { system("cls"); API::Utils::Logger::message(API::Utils::MessageType::INF, "\n\t\t\t", m_title); }
			
			void displayEntityData(std::shared_ptr<Entity::Entity>& t_entity);
			void initMovesGenerator(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator, std::shared_ptr<Entity::Entity>& t_entity);
			void swapEntityTurns(const std::shared_ptr<Entity::Entity>& t_entityOnTurn);
			void endTurn(const std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator);
			
			// -------------------- //
			// private game helpers //
			// -------------------- //
			// game state (e.g. undo/redo ...) helpers
			void undoHelper();
			void redoHelper();
			
			void winHelper(API::Events::GameSystemState& t_finalGameState);
			void quitHelper();
			// timer helper
			void delayHelper(double t_maxDelayTime);
	};
}

#endif // !GAME_HPP