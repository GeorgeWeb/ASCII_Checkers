#ifndef GAME_HPP
#define GAME_HPP

// project includes
#include "API/Board.hpp"

// std::includes
#include <memory>
#include <vector>

namespace CheckerZ
{
	enum class Gameplay : const char
	{
		MOVE = '1',
		TAKE = '2'
	};

	class Game
	{
		private:
			std::unique_ptr<API::Board> m_gameBoard;
			
			bool m_isRunning = false;
			bool m_nextTurn = false;
			
		public:
			Game();
			~Game();
			
			inline bool getIsRunning() const { return m_isRunning; }
			inline bool getNextTurn() const { return m_nextTurn; }

			void begin();
			void end();
			void update();
			void draw();
	};
}

#endif // !GAME_HPP