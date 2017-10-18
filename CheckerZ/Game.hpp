#ifndef GAME_HPP
#define GAME_HPP

// project includes
#include "API/Board.hpp"
#include "API/Events/EventManager.hpp"
#include "Entity/Player/Player.hpp"

// std::includes
#include <memory>
#include <vector>

namespace CheckerZ
{
	class Game final
	{
		enum class TurnState : uint8
		{
			FIRST,
			BEGIN,
			END
		};

		private:
			std::string m_title;
			
			std::unique_ptr<API::Board> m_gameBoard;
			API::Events::GameSystemState m_gameState;
			TurnState m_turnState;

			std::shared_ptr<Entity::Player::Player> m_player;

		public:
			Game();
			~Game();
			
			inline bool getIsRunning() const { return m_gameState == API::Events::GameSystemState::RUN; }
			inline bool getNextTurn() const { return m_turnState == TurnState::END; }
			
			inline void setTitle(const std::string& t_title = "") { m_title = !t_title.empty() ? t_title : m_title; }

			void begin();
			void update();
			void draw();
			void end();

		private:
			inline void setGameState(const API::Events::GameSystemState& t_newState) { m_gameState = t_newState; }
			inline void setTurnState(const TurnState& t_newState) { m_turnState = t_newState; }
			inline void printTitle() const { system("cls"); API::Logger::message(API::MessageType::INF, "\n\n\n\t\t\t\t\t       ", m_title); }

		private:
			Game(const Game&) = delete;
			Game(Game&&) = delete;
	};
}

#endif // !GAME_HPP