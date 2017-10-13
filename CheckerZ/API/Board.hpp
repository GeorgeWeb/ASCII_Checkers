#ifndef BOARD_HPP
#define BOARD_HPP
#ifdef PRAGMA ONCE
#define pragma_once
#endif

// project includes
#include "../Parallelism/Parallel.hpp"

// std::includes
#include <array>

namespace CheckerZ
{
	namespace TABLE
	{
		// define a square of the grid
		using square = unsigned char;
		// define the grid of the board
		template<const size_t Size>
		using grid = std::array<square, Size>;
		// define a board matrix
		template<const size_t SizeX, const size_t SizeY>
		using board = std::array<grid<SizeY>, SizeX>;
	}

	class Board
	{
		static constexpr size_t s_boardX = 8;
		static constexpr size_t s_boardY = 8;

		private:
			TABLE::board<s_boardX, s_boardY> m_board;
		public:
			Board();
			~Board();

			inline const TABLE::board<s_boardX, s_boardY> &getBoard() const { return m_board; }

			void populate();
			void display();
	};
}

#endif // !BOARD_HPP
