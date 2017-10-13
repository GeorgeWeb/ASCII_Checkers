#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "../Common.hpp"
#include "../Parallelism/Parallel.hpp"

// std::includes
#include <array>

namespace CheckerZ
{
	#pragma region Checkers Table Properties
	// define a square of the grid
	using square = uchar;
	// define the grid of the board
	template<const uint32 Size>
	using grid = std::array<square, Size>;
	// define a board matrix
	template<const uint32 SizeX, const uint32 SizeY>
	using board = std::array<grid<SizeY>, SizeX>;
	#pragma endregion

	class Board
	{
		static constexpr uint32 s_boardX = 8;
		static constexpr uint32 s_boardY = 8;

		private:
			board<s_boardX, s_boardY> m_board;
		public:
			Board();
			~Board();

			inline const board<s_boardX, s_boardY>& const getBoard() const { return m_board; }

			void populate();
			void display();
	};
}

#endif // !BOARD_HPP
