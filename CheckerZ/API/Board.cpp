// project includes
#include "Board.hpp"

// std::includes
#include <iostream>
#include <algorithm>

namespace CheckerZ { namespace API {
	
	Board::Board()
	{ }

	Board::~Board()
	{ }

	std::array<square, 12> Board::getPawnsByColor(const std::string& t_color)
	{
		// Throw error for invalid argument
		if (t_color == "") return std::array<square, 12>();
		
		// TODO: return all pawns from the chosen color
		if (t_color == "Black")
		{
			return std::array<square, 12>();
		}
		else if (t_color == "Red")
		{
			return std::array<square, 12>();
		}
	}
	
	void Board::setPos(vec2 t_pos)
	{
		for (const auto &pos : t_pos)
		{
			switch (pos.first)
			{
				case 'A':
					switch (pos.second)
					{
						case 1:
							break;
						case 2:
							m_board[0][1] = 'X';
							break;
						case 3:
							break;
						case 4:
							break;
						case 5:
							break;
						case 6:
							break;
						case 7:
							break;
						case 8:
							break;
					}
				break;
				
				default:
					break;
			}
		}
	}

	void Board::populate()
	{
		// TODO:
		// Board will accept squares
		// Pawn meshes will be assigned as 'B' or 'R' in specific cases
		// Array of empty slots will be init in Board.hpp
		// Squares will equal pawn meshes but those supposed to be empty or '.' will be stored in the empty vector
		// The squares will be equal to all the pawn meshes and to all the empty vectors
		// 1. When a pawn mesh is taken it will go to the empty vector
		// 2. When a pawn mesh moves it will swap with a point from the empty vector on the position it is going
		// 3. If a pawn mesh wants to move and there's another pawn mesh on that position(diagonally) then return;

		uint16 count{ 0 };
		std::for_each(m_board.begin(), m_board.end(), [&](auto& grid)
		{
			std::for_each(grid.begin(), grid.end(), [&](auto& square)
			{
				// Player1's pawns
				if (count < 24)
				{
					if (count < 8)
					{
						square = (count % 2) ? 'B' : '.';
					}
					else if (count >= 8 && count < 16)
					{
						square = !(count % 2) ? 'B' : '.';
					}
					else if (count >= 16 && count < 24)
					{
						square = (count % 2) ? 'B' : '.';
					}
				}
				// Player2's pawns
				else if (count >= 40)
				{
					if (count < 48)
					{
						square = !(count % 2) ? 'R' : '.';
					}
					else if (count >= 48 && count < 56)
					{
						square = (count % 2) ? 'R' : '.';
					}
					else if (count >= 56 && count < 64)
					{
						square = !(count % 2) ? 'R' : '.';
					}
				}
				// Rest of the grid
				else
				{
					square = '.';
				}

				// ...
				count++;
			});
		});
	}
	
	void Board::display() const
	{
		std::cout << "\n\n\n\n";
		uint16 count{ 1 };
		std::for_each(m_board.cbegin(), m_board.cend(), [&](auto& grid)
		{
			std::cout << "\t\t\t\t\t\t";
			std::for_each(grid.cbegin(), grid.cend(), [&](const auto square)
			{
				std::cout << square << " ";
				if (count++ % 8 == 0) std::cout << "\n";
			});
		});
	}

} }