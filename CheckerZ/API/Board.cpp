// project includes
#include "Board.hpp"

// std::includes
#include <iostream>
#include <algorithm>

namespace CheckerZ { namespace API {

	bool operator==(Pawn& t_lhs, Pawn& t_rhs);
	bool operator!=(Pawn& t_lhs, Pawn& t_rhs);

	ActionState Board::move(const Position &t_posFrom, const Position& t_posTo)
	{
		ActionState state;

		// check if a killing jump is happening
		bool canKill = (std::abs(static_cast<int>(t_posFrom.first - t_posTo.first)) + std::abs(static_cast<int>(t_posFrom.second - t_posTo.second)) == 4);
		// move pawn
		swapPawns(m_board[t_posFrom.first][t_posFrom.second], m_board[t_posTo.first][t_posTo.second], canKill);

		return canKill ? ActionState::JUMP : ActionState::MOVE;
	}

	void Board::evolve(Pawn& t_pawn)
	{
		// TODO: Evolve a man pawn into a king pawn...
	}

	void Board::swapPawns(Pawn& t_lhs, Pawn& t_rhs, bool canKill)
	{
		// check if kill on jump is possible
		if (canKill)
		{
			killPawn(m_board[(t_lhs.getCoordX() + t_rhs.getCoordX()) / 2][(t_lhs.getCoordY() + t_rhs.getCoordY()) / 2]);
		}

		// swap pawns values on move
		std::swap(t_lhs.getMesh(), t_rhs.getMesh());
		std::swap(t_lhs.getColor(), t_rhs.getColor());
		t_lhs.getPos().swap(t_rhs.getPos());
	}

	void Board::killPawn(Pawn& t_pawn)
	{
		uint8 emptyMesh = ' ';
		std::string emptyColor = "Empty";
		
		// swap pawns values on kill/take
		std::swap(t_pawn.getMesh(), emptyMesh);
		std::swap(t_pawn.getColor(), emptyColor);
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
					pawn.setValues(' ', "Empty", row, col);
				else
				{
					// Entity1's pawns
					if (row < 3)
						pawn.setValues('b', "Black", row, col);
					// Entity2's pawns
					else if (row > 4)
						pawn.setValues('r', "Red", row, col);
					// Empty space
					else
						pawn.setValues(' ', "Empty", row, col);
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