#include "MovesGenerator.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	void MovesGenerator::generatePossibleMoves(std::shared_ptr<Board> t_board, const std::string& t_color, Pawn* replayablePawn)
	{
		// auto tempBoard = *t_board;

		switch (t_color[0])
		{
			case 'B': ///> Black
				for (auto x = 0; x < t_board->getBoard().size(); x++)
				{
					for (auto y = 0; y < t_board->getBoard().size(); y++)
					{
						if (t_board->getBoardPawn(x, y).getColor() == "Black")
						{
							if (t_board->getBoardPawn(x, y).isKing())
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
								if (t_board->getGridInfo(x + 1, y - 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 1, y - 1) });
								}
								// top-right-move
								if (t_board->getGridInfo(x + 1, y + 1) == GridInfo::EMPTY)
								{
									m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 1, y + 1) });
								}
								// top-left-jump
								if (t_board->getGridInfo(x + 1, y - 1) == GridInfo::RED && t_board->getGridInfo(x + 2, y - 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y - 2) });
								}
								// top-right-jump
								if (t_board->getGridInfo(x + 1, y + 1) == GridInfo::RED && t_board->getGridInfo(x + 2, y + 2) == GridInfo::EMPTY)
								{
									m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x + 2, y + 2) });
								}
							}
						}
					}
				}
				break;
			case 'R': ///> Red
				for (auto x = 0; x < t_board->getBoard().size(); x++)
				{
					for (auto y = 0; y < t_board->getBoard().size(); y++)
					{
						if (t_board->getBoardPawn(x, y).getColor() == "Red")
						{
							// X is COL, Y is ROW !!!
							// bottom-left-move
							if (t_board->getGridInfo(x - 1, y - 1) == GridInfo::EMPTY)
							{
								m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 1, y - 1) });
							}
							// bottom-right-move
							if (t_board->getGridInfo(x - 1, y + 1) == GridInfo::EMPTY)
							{
								m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 1, y + 1) });
							}
							// bottom-left-jump
							if (t_board->getGridInfo(x - 1, y - 1) == GridInfo::BLACK && t_board->getGridInfo(x - 2, y - 2) == GridInfo::EMPTY)
							{
								m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y - 2) });
							}
							// bottom-right-jump
							if (t_board->getGridInfo(x - 1, y + 1) == GridInfo::BLACK && t_board->getGridInfo(x - 2, y + 2) == GridInfo::EMPTY)
							{
								m_possibleMoves.push_back({ std::make_pair(x, y), std::make_pair(x - 2, y + 2) });
							}
						}
					}
				}
				break;
			case 'E': ///> Empty
			default:
				break;
		}

		std::sort(m_possibleMoves.begin(), m_possibleMoves.end());
	}

} } }