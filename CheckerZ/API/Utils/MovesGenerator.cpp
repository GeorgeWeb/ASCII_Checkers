#include "MovesGenerator.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	void MovesGenerator::generatePossibleMoves(std::shared_ptr<Board> t_board, const std::string& t_color, std::shared_ptr<Pawn> t_lastPlayedPawn)
	{
		auto tempBoard = *t_board;
		
		if (t_lastPlayedPawn && t_lastPlayedPawn->getColor() == t_color)
		{
			auto x = t_lastPlayedPawn->getPos().first;
			auto y = t_lastPlayedPawn->getPos().second;
			//  Black player was on turn
			if (t_lastPlayedPawn->getColor() == "Black")
			{
				if (t_lastPlayedPawn->isKing())
				{
					checkLeftJump(tempBoard, x, y, "Top");
					checkRightJump(tempBoard, x, y, "Top");

					checkLeftJump(tempBoard, x, y, "Bottom");
					checkRightJump(tempBoard, x, y, "Bottom");
				}
				else
				{
					checkLeftJump(tempBoard, x, y, "Top");
					checkRightJump(tempBoard, x, y, "Top");
				}
			}
			// Red player was on turn
			if (t_lastPlayedPawn->getColor() == "Red")
			{
				if (t_lastPlayedPawn->isKing())
				{
					checkLeftJump(tempBoard, x, y, "Top");
					checkRightJump(tempBoard, x, y, "Top");
					checkLeftJump(tempBoard, x, y, "Bottom");
					checkRightJump(tempBoard, x, y, "Bottom");
				}
				else
				{
					checkLeftJump(tempBoard, x, y, "Bottom");
					checkRightJump(tempBoard, x, y, "Bottom");
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
								checkLeftMove(tempBoard, x, y, "Top");
								checkRightMove(tempBoard, x, y, "Top");
								checkLeftJump(tempBoard, x, y, "Top");
								checkRightJump(tempBoard, x, y, "Top");

								checkLeftMove(tempBoard, x, y, "Bottom");
								checkRightMove(tempBoard, x, y, "Bottom");
								checkLeftJump(tempBoard, x, y, "Bottom");
								checkRightJump(tempBoard, x, y, "Bottom");
							}
							else
							{
								checkLeftMove(tempBoard, x, y, "Top");
								checkRightMove(tempBoard, x, y, "Top");
								checkLeftJump(tempBoard, x, y, "Top");
								checkRightJump(tempBoard, x, y, "Top");
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
								checkLeftMove(tempBoard, x, y, "Top");
								checkRightMove(tempBoard, x, y, "Top");
								checkLeftJump(tempBoard, x, y, "Top");
								checkRightJump(tempBoard, x, y, "Top");

								checkLeftMove(tempBoard, x, y, "Bottom");
								checkRightMove(tempBoard, x, y, "Bottom");
								checkLeftJump(tempBoard, x, y, "Bottom");
								checkRightJump(tempBoard, x, y, "Bottom");
							}
							else
							{
								checkLeftMove(tempBoard, x, y, "Bottom");
								checkRightMove(tempBoard, x, y, "Bottom");
								checkLeftJump(tempBoard, x, y, "Bottom");
								checkRightJump(tempBoard, x, y, "Bottom");
							}
						}
					}
				}
				break;
			case 'E': ///> Empty
			default:
				break;
		}
	}

	void MovesGenerator::reset(std::shared_ptr<Board> t_board, const std::string & t_color, std::shared_ptr<Pawn> t_lastPlayedPawn)
	{
		m_possibleMoves.clear();
		generatePossibleMoves(t_board, t_color, t_lastPlayedPawn);
	}
	
	// ------------------- //
	// check moves helpers //
	// ------------------- //
	void MovesGenerator::checkLeftMove(Board& t_board, int x, int y, const std::string &t_pos)
	{		
		if (t_pos == "Top")
		{
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 1, y - 1) });
			}
		}

		if (t_pos == "Bottom")
		{
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 1, y - 1) });
			}
		}
	}

	void MovesGenerator::checkRightMove(Board& t_board, int x, int y, const std::string &t_pos)
	{
		if (t_pos == "Top")
		{
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 1, y + 1) });
			}
		}

		if (t_pos == "Bottom")
		{
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 1, y + 1) });
			}
		}
	}

	void MovesGenerator::checkLeftJump(Board& t_board, int x, int y, const std::string &t_pos)
	{
		if (t_pos == "Top")
		{
			if (t_board.getGridInfo(x + 1, y - 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
			}
		}

		if (t_pos == "Bottom")
		{
			if (t_board.getGridInfo(x - 1, y - 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
			}
		}
	}

	void MovesGenerator::checkRightJump(Board& t_board, int x, int y, const std::string &t_pos)
	{
		if (t_pos == "Top")
		{
			if (t_board.getGridInfo(x + 1, y + 1) == GridInfo::RED && t_board.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
			}
		}

		if (t_pos == "Bottom")
		{
			if (t_board.getGridInfo(x - 1, y + 1) == GridInfo::BLACK && t_board.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
			{
				m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
			}
		}
	}

} } }