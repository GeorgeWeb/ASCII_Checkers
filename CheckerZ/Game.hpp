#ifndef GAME_HPP
#define GAME_HPP

// project includes
#include "API/Board.hpp"

// std::includes
#include <memory>

namespace CheckerZ
{
	enum class Gameplay : char
	{
		MOVE = '1',
		TAKE = '2'
	};

	class Game
	{
		private:
			std::unique_ptr<Board> m_gameBoard;
			
			bool m_isRunning = false;
			bool m_nextTurn = false;
		
		public:
			Game();
			~Game();
			
			inline const bool &getIsRunning() const { return m_isRunning; }
			inline const bool &getNextTurn() const { return m_nextTurn; }

			void Begin();
			void End();
			void Update();
			void Draw();
	};
}

#endif // !GAME_HPP