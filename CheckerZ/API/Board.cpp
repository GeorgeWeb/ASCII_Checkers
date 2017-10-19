// project includes
#include "Board.hpp"

// std::includes
#include <iostream>
#include <algorithm>

namespace CheckerZ { namespace API {
	
	Board::Board()
	{ 
		m_emptySlots.reserve(40);
		m_blackPawns.reserve(12);
		m_redPawns.reserve(12);
	}

	Board::~Board()
	{ }

	const std::vector<square>& Board::getEmptySlots()
	{
		return m_emptySlots;
	}

	const std::vector<square>& Board::getPawnsByColor(const std::string& t_color)
	{		
		// TODO: return all pawns from the chosen color
		if (t_color == "Black")
		{
			return m_blackPawns;
		}
		else if (t_color == "Red")
		{
			return m_redPawns;
		}
	}
	
	void Board::translate(const vec2& t_posFrom, const vec2 &t_posTo)
	{
		for (const auto &posFrom : t_posFrom)
		{
			// get the entity's own picked pawn
			auto&& pawnPick = m_board['H' - posFrom.first][posFrom.second - 1];
			for (const auto &posTo : t_posTo)
			{
				// get the other pawn picked for action by the entity
				auto&& actionPick = m_board['H' - posTo.first][posTo.second - 1];
				
				// Do the movement
				std::swap(pawnPick, actionPick);
			}
		}
	}

	void Board::erase(const vec2& t_posFrom, const vec2 &t_posTo)
	{
		// TODO: ...
	}

	void Board::populate()
	{
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

				// Construct arrays to be assigned to each player's pawns
				if (square == 'B')
					m_blackPawns.push_back(square);
				else if (square == 'R')
					m_redPawns.push_back(square);
				else
					m_emptySlots.push_back(square);

				count++;
			});
		});
	}
	
	void Board::display() const
	{
		std::cout << "\n\n\n\n";
		uint16 count{ 1 };
		uint16 numberLabel{ 8 };
		std::for_each(m_board.cbegin(), m_board.cend(), [&](auto& grid)
		{
			std::cout << "\t\t\t\t\t\t" << numberLabel-- << "| ";
			std::for_each(grid.cbegin(), grid.cend(), [&](const auto square)
			{
				std::cout << square << " ";
				if (count++ % 8 == 0) std::cout << "\n";
			});
		});
		std::cout << "\t\t\t\t\t\t" << "-------------------" << "\n";
		std::cout << "\t\t\t\t\t\t" << "   A B C D E F G H" << "\n";
	}

} }