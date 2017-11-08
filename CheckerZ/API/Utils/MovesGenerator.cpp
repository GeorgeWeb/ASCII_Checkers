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
					// TODO: ...
				}
				else
				{
					// top-left-jump
					if (tempBoard.getGridInfo(x + 1, y - 1) == GridInfo::RED && tempBoard.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
					{
						m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
					}
					// top-right-jump
					if (tempBoard.getGridInfo(x + 1, y + 1) == GridInfo::RED && tempBoard.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
					{
						m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
					}
				}
			}
			// Red player was on turn
			if (t_lastPlayedPawn->getColor() == "Red")
			{
				if (t_lastPlayedPawn->isKing())
				{
					// TODO: ...
				}
				else
				{
					// bottom-left-jump
					if (tempBoard.getGridInfo(x - 1, y - 1) == GridInfo::BLACK && tempBoard.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
					{
						m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
					}
					// bottom-right-jump
					if (tempBoard.getGridInfo(x - 1, y + 1) == GridInfo::BLACK && tempBoard.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
					{
						m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
					}
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
								// Do king checks
								// if( tempBoard.getGridInfo (x-1,y-1) == 0 ; -> 
								// if == 1 -> 
								// for King ( i=0;i<3;i++)
								// { tembBoard.getGridInfo (x + pick.x[i]) , y + pick.y[i]) == 0 ->
								// if == 1 ->
								// if getgridinfo = red -> if (get grid info (x + 2* pick.x[i], y + 2*pick.y[i])== empty then add move
							}
							else
							{
								// X is COL, Y is ROW !!!
								// top-left-move
								if (tempBoard.getGridInfo(x + 1, y - 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 1, y - 1) });
								}
								// top-right-move
								if (tempBoard.getGridInfo(x + 1, y + 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 1, y + 1) });
								}
								// top-left-jump
								if (tempBoard.getGridInfo(x + 1, y - 1) == GridInfo::RED && tempBoard.getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
								}
								// top-right-jump
								if (tempBoard.getGridInfo(x + 1, y + 1) == GridInfo::RED && tempBoard.getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
								}
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
								// Do king checks
								// if( tempBoard.getGridInfo (x-1,y-1) == 0 ; -> 
								// if == 1 -> 
								// for King ( i=0;i<3;i++)
								// { tembBoard.getGridInfo (x + pick.x[i]) , y + pick.y[i]) == 0 ->
								// if == 1 ->
								// if getgridinfo = red -> if (get grid info (x + 2* pick.x[i], y + 2*pick.y[i])== empty then add move
							}
							else
							{
								// X is COL, Y is ROW !!!
								// bottom-left-move
								if (tempBoard.getGridInfo(x - 1, y - 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 1, y - 1) });
								}
								// bottom-right-move
								if (tempBoard.getGridInfo(x - 1, y + 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 1, y + 1) });
								}
								// bottom-left-jump
								if (tempBoard.getGridInfo(x - 1, y - 1) == GridInfo::BLACK && tempBoard.getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
								}
								// bottom-right-jump
								if (tempBoard.getGridInfo(x - 1, y + 1) == GridInfo::BLACK && tempBoard.getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.insert({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
								}
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

} } }