// project includes
#include "Board.hpp"

// std::includes
#include <iostream>
#include <algorithm>

namespace CheckerZ { namespace API {

	bool operator==(Pawn& t_lhs, Pawn& t_rhs);
	bool operator!=(Pawn& t_lhs, Pawn& t_rhs);

	void Board::move(const Position &t_posFrom, Position&& t_posTo)
	{
		// check for jumps
		// if | getBoardPawn(t_posFrom).getCoordX() - getBoardPawn(t_posTo).getCoordX() | + 
		//	  | getBoardPawn(t_posFrom).getCoordY() - getBoardPawn(t_posTo).getCoordY() | == 4
		// => Jump: auto pawnToKill = 
		//				m_board[getBoardPawn(t_posFrom).getCoordX() + getBoardPawn(t_posTo).getCoordX() / 2] 
		//					   [getBoardPawn(t_posFrom).getCoordY() + getBoardPawn(t_posTo).getCoordY() / 2];
		//			pawnToKill.getMesh() = ' '; pawnToKill.getColor() = 'Empty'
		// ...
		throw std::runtime_error("Moved");
	}

	void Board::evolve(Pawn& t_pawn)
	{
	}

	void Board::swapPawns(Pawn& t_lhs, Pawn& t_rhs)
	{
		// Swap values between of your pawn left pawn and the one you will take / jump on
		std::swap(t_lhs.getMesh(), t_rhs.getMesh());
		std::swap(t_lhs.getColor(), t_rhs.getColor());
		std::swap(t_lhs.getCoordX(), t_rhs.getCoordX());
		std::swap(t_lhs.getCoordY(), t_rhs.getCoordY());
	}

	void Board::killPawn(Pawn& t_pawn)
	{
		// TODO: ...
	}

	GridInfo Board::getGridInfo(int t_row, int t_col)
	{
		GridInfo gridInfo = GridInfo::EOB;
		// check if the coordinates get out of bounds & return
		if (t_row < 0 || t_col < 0 || t_row >= m_board.size() || t_col >= m_board.size())
			return gridInfo;
		
		// return the color of the pawn by the coordinates
		auto colorPick = m_board[t_row][t_col].getColor();
		return gridInfo = colorPick == "Black" ? GridInfo::BLACK : colorPick == "Red" ? GridInfo::RED 
			: colorPick == "Empty" ? GridInfo::EMPTY : GridInfo::EOB;
	}

	void Board::populate()
	{
		for(size_t row = 0; row < m_board.size(); row++)
		{
			for (size_t col = 0; col < m_board.size(); col++)
			{
				auto& pawn = m_board[row][col];

				if (((row + col) % 2) == 0)
					pawn.setValues(' ', "Empty", std::move(row), std::move(col));
				else
				{
					// Entity1's pawns
					if (row < 3)
						pawn.setValues('b', "Black", std::move(row), std::move(col));
					// Entity2's pawns
					else if (row > 4)
						pawn.setValues('r', "Red", std::move(row), std::move(col));
					// Empty space
					else
						pawn.setValues(' ', "Empty", std::move(row), std::move(col));
				}
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

	bool operator==(API::Pawn& t_lhs, API::Pawn& t_rhs)
	{
		return (
			// x coordinates check
			t_lhs.getCoordX() == t_rhs.getCoordX() &&
			// y coordinates check
			t_lhs.getCoordY() == t_rhs.getCoordY());/* &&
			// mesh check
			t_lhs.getMesh() == t_rhs.getMesh() &&
			// color check
			t_lhs.getColor() == t_rhs.getColor());*/
	}

	bool operator!=(API::Pawn& t_lhs, API::Pawn& t_rhs)
	{
		return !(t_lhs == t_rhs);
	}

} }