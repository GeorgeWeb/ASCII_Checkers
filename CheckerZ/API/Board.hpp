#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "../Common.hpp"

// std::includes
#include <array>

namespace CheckerZ { namespace API {
	
	#pragma region Checkers Table Properties
	// define a square of the grid
	using square = uint8;
	// define the grid of the board
	template<const uint16 Size>
	using grid = std::array<square, Size>;
	// define a board matrix
	template<const uint16 SizeX, const uint16 SizeY>
	using board = std::array<grid<SizeY>, SizeX>;
	#pragma endregion

	class Board
	{
		static constexpr uint16 s_boardX = 8;
		static constexpr uint16 s_boardY = 8;

		private:
			board<s_boardX, s_boardY> m_board;
		
		public:
			Board();
			~Board();

			inline const board<s_boardX, s_boardY>& const getBoard() const { return m_board; }

			void populate();
			void display() const;
		
		public:
			void traverse(std::function<void(uint16)> t_action)
			{
				uint16 count{ 0 };
				std::for_each(m_board.cbegin(), m_board.cend(), [&](const grid<s_boardY>& grid)
				{
					std::for_each(grid.cbegin(), grid.cend(), [&](const square square)
					{
						std::invoke(t_action, count);
						// counts every square in the grid
						count++;
					});
				});
			}
		
		private:
			Board(const Board&) = delete;
			Board(Board&&) = delete;
	};

} }

#endif // !BOARD_HPP
