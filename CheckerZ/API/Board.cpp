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

	void Board::swapBoardGrids(Pawn& t_lhs, Pawn& t_rhs)
	{
		std::swap(t_lhs.getMesh(), t_rhs.getMesh());
		std::swap(t_lhs.getColor(), t_rhs.getColor());
	}

	void Board::populate()
	{
		for(size_t row = 0; row < m_board.size(); row++)
		{
			for (size_t col = 0; col < m_board.size(); col++)
			{
				auto& pawn = m_board[row][col];

				if (((row + col) % 2) == 0)
					pawn.setValues('.', "White");
				else
				{
					// Entity1's pawns
					if (row < 3)
						pawn.setValues('B', "Black");
					// Entity2's pawns
					else if (row > 4)
						pawn.setValues('R', "Red");
					// Empty space
					else
						pawn.setValues('.', "White");
				}

				// Construct arrays to be assigned to each entity's pawns
				if (pawn.getColor() == "Black")
					m_blackPawns.push_back(pawn);
				else if (pawn.getColor() == "Red")
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
			std::for_each(grid.cbegin(), grid.cend(), [&](auto pawn)
			{
				std::cout << pawn.getMesh();
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