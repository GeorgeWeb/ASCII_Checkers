#include "MovesGenerator.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	// TODO: Fix King movement

	void MovesGenerator::generatePossibleMoves(std::shared_ptr<Board> t_board, const std::string& t_color, std::shared_ptr<Pawn> t_lastPlayedPawn)
	{
		Board tempBoard = *t_board;
		
		if (t_lastPlayedPawn && t_lastPlayedPawn->getColor() == t_color)
		{
			auto x = t_lastPlayedPawn->getPos().first;
			auto y = t_lastPlayedPawn->getPos().second;
			//  Black player was on turn
			if (t_lastPlayedPawn->getColor() == "Black")
			{
				if (t_lastPlayedPawn->isKing())
				{
					// check king jumps
					checkKingJumps(tempBoard, x, y, "Black");
				}
				else
				{
					// check jumps
					checkLeftJump(tempBoard, x, y, "Black");
					checkRightJump(tempBoard, x, y, "Black");
				}
			}
			// Red player was on turn
			if (t_lastPlayedPawn->getColor() == "Red")
			{
				if (t_lastPlayedPawn->isKing())
				{
					// check king jumps
					checkKingJumps(tempBoard, x, y, "Red");
				}
				else
				{
					// check jumps
					checkLeftJump(tempBoard, x, y, "Red");
					checkRightJump(tempBoard, x, y, "Red");
				}
			}
		}
		else
		switch (t_color[0])
		{
			case 'B': ///> Black
				for (auto x = 0; x < tempBoard.getBoard().size(); x++)
				{
					for (auto y = 0; y < tempBoard.getBoard().size(); y++)
					{
						if (tempBoard.getBoardPawn(x, y).getColor() == "Black")
						{
							if (tempBoard.getBoardPawn(x, y).isKing())
							{
								// check king moves
								checkLeftMove(tempBoard, x, y, "Black");
								checkRightMove(tempBoard, x, y, "Black");
								checkLeftMove(tempBoard, x, y, "Red");
								checkRightMove(tempBoard, x, y, "Red");
								// check king jumps
								checkKingJumps(tempBoard, x, y, "Black");
							}
							else
							{
								// check moves
								checkLeftMove(tempBoard, x, y, "Black");
								checkRightMove(tempBoard, x, y, "Black");
								// check jumps
								checkLeftJump(tempBoard, x, y, "Black");
								checkRightJump(tempBoard, x, y, "Black");
							}
						}
					}
				}
				break;
			case 'R': ///> Red
				for (auto x = 0; x < tempBoard.getBoard().size(); x++)
				{
					for (auto y = 0; y < tempBoard.getBoard().size(); y++)
					{
						if (tempBoard.getBoardPawn(x, y).getColor() == "Red")
						{
							if (tempBoard.getBoardPawn(x, y).isKing())
							{
								// check king moves
								checkLeftMove(tempBoard, x, y, "Red");
								checkRightMove(tempBoard, x, y, "Red");
								checkLeftMove(tempBoard, x, y, "Black");
								checkRightMove(tempBoard, x, y, "Black");
								// check king jumps
								checkKingJumps(tempBoard, x, y, "Red");
							}
							else
							{
								// check moves
								checkLeftMove(tempBoard, x, y, "Red");
								checkRightMove(tempBoard, x, y, "Red");
								// check jumps
								checkLeftJump(tempBoard, x, y, "Red");
								checkRightJump(tempBoard, x, y, "Red");
							}
						}
					}
				}
				break;
			case 'E': ///> Empty
			default:
				break;
		}

		// sort the list to make searching it from Player or AI faster via binary search
		std::sort(m_possibleMoves.begin(), m_possibleMoves.end());
	}

	void MovesGenerator::reset(std::shared_ptr<Board> t_board, const std::string & t_color, std::shared_ptr<Pawn> t_lastPlayedPawn)
	{
		m_possibleMoves.clear();
		generatePossibleMoves(t_board, t_color, t_lastPlayedPawn);
	}
	
	// ------------------- //
	// check moves helpers //
	// ------------------- //
	void MovesGenerator::checkKingJumps(Board& t_board, int x, int y, const std::string& t_color)
	{
		// check left and right for black
		if (t_color == "Black")
		{
			// top left
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
			}
			// top right
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
			}
			// bottom left
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::RED && t_board.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
			}
			// bottom right
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::RED && t_board.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
			}
		}
		
		// check left and right for red
		if (t_color == "Red")
		{
			// bottom left
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
			}
			// bottom right
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
			}
			// top left
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::BLACK && t_board.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
			}
			// top right
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::BLACK && t_board.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
			}
		}
	}

	void MovesGenerator::checkLeftMove(Board& t_board, int x, int y, const std::string &t_color)
	{		
		if (t_color == "Black")
		{
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 1, y - 1) });
			}
		}

		if (t_color == "Red")
		{
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 1, y - 1) });
			}
		}
	}

	void MovesGenerator::checkRightMove(Board& t_board, int x, int y, const std::string &t_color)
	{
		if (t_color == "Black")
		{
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 1, y + 1) });
			}
		}

		if (t_color == "Red")
		{
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 1, y + 1) });
			}
		}
	}

	void MovesGenerator::checkLeftJump(Board& t_board, int x, int y, const std::string &t_color)
	{
		if (t_color == "Black")
		{
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
			}
		}
		
		if (t_color == "Red")
		{
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
			}
		}
	}

	void MovesGenerator::checkRightJump(Board& t_board, int x, int y, const std::string &t_color)
	{
		if (t_color == "Black")
		{
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
			}
		}

		if (t_color == "Red")
		{
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
			}
		}
	}

} } }