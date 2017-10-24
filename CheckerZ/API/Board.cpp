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
	{ 
		// TODO: Free memory from pawns
	}

	const std::vector<Pawn>& Board::getEmptySlots()
	{
		return m_emptySlots;
	}

	const std::vector<Pawn>& Board::getPawnsByColor(const std::string& t_color)
	{		
		// TODO: return all pawns from the chosen color
		if (t_color == "Black")
			return m_blackPawns;
		else if (t_color == "Red")
			return m_redPawns;
	}
	
	void Board::translate(const vec2& t_posFrom, const vec2& t_posTo)
	{
		// get the entity's own picked pawn
		auto&& pawnPick = m_board[t_posFrom.first - 'A'][t_posFrom.second - 1];
		// get the other pawn picked for action by the entity
		auto&& actionPick = m_board[t_posTo.first - 'A'][t_posTo.second - 1];
				
		// Do the movement
		std::swap(pawnPick, actionPick);
	}

	void Board::erase(const vec2& t_posFrom, const vec2& t_posTo)
	{
		// TODO: ...
	}

	void Board::populate()
	{
		for(size_t row = 0; row < m_board.size(); row++)
		{
			for (size_t col = 0; col < m_board.size(); col++)
			{
				auto& pawn = m_board[row][col];

				if (((row + col) % 2) == 0)
				{
					pawn.mesh = '.';
					pawn.color = "White";
				}
				else
				{
					// Entity1's pawns
					if (row < 3)
					{
						pawn.mesh = 'B';
						pawn.color = "Black";
					}
					// Entity2's pawns
					else if (row > 4)
					{
						pawn.mesh = 'R';
						pawn.color = "Red";
					}
					// Empty space
					else
					{
						pawn.mesh = '.';
						pawn.color = "White";
					}
				}

				// Construct arrays to be assigned to each entity's pawns
				if (pawn.color == "Black")
					m_blackPawns.push_back(pawn);
				else if (pawn.color == "Red")
					m_redPawns.push_back(pawn);
				else
					m_emptySlots.push_back(pawn);
			}
		}
	}
	
	void Board::display() const
	{
		std::cout << "\n";
		std::cout << "\t" << "      +===+===+===+===+===+===+===+===+===+===+" << "\n";
		std::cout << "\t" << "      | / | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | \\ |" << "\n";
		std::cout << "\t" << "      +===+===+===+===+===+===+===+===+===+===+" << "\n";
		
		uint16 count{ 1 };
		uint16 sideLbl{ 0 };
		std::for_each(m_board.cbegin(), m_board.cend(), [&](auto grid)
		{
			std::cout << "\t" << "      [ " << char(sideLbl + 'A') << " ] ";
			std::for_each(grid.cbegin(), grid.cend(), [&](const auto pawn)
			{
				std::cout << pawn.mesh;
				(count % 8 == 0) ? std::cout << " [ " : std::cout << " | ";

				if (count % 8 == 0)
				{
					std::cout << char(sideLbl + 'A') << " ]\n";
					if(count < 64)
						std::cout << "\t" << "      +---+-------------------------------+---+" << "\n";
					else
						std::cout << "\t" << "      +===+===+===+===+===+===+===+===+===+===+" << "\n";
				}

				count++;
			});
			sideLbl++;
		});
		
		std::cout << "\t" << "      | \\ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | / |" << "\n";
		std::cout << "\t" << "      +===+===+===+===+===+===+===+===+===+===+" << "\n";
	}

} }