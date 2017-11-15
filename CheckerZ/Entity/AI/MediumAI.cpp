#include "AI.hpp"
#include <map>

namespace CheckerZ { namespace Entity { namespace AI {

	void MediumAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);
		
		// custom 'offensive' greedy algorithm
		
		std::map<uint16, Movement> moveOrders;
		auto possibleMoves = t_moveGenerator->getPossibleMoves();

		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return;

		std::for_each(possibleMoves.begin(), possibleMoves.end(), [&](const Movement& move)
		{
			uint16 order = std::abs(static_cast<int>(move.first.first - move.second.first) + std::abs(static_cast<int>(move.first.second - move.second.second)));
			
			// make order higher if the pawn to move is a king
			if (m_board->getBoardPawn(move.first).isKing())
			{
				// find the pawn in between the jump
				if (order < 4) ///> no jump, though
				{
					// if the order doesn't match a jump move but the pawn is still a king pawn
					order += 1; ///> make it 3
				}
				else ///> yey, jumping
				{
					auto possibleEnemyPawn = m_board->getBoard()[(m_board->getBoardPawn(move.first).getCoordX() + m_board->getBoardPawn(move.second).getCoordX()) / 2]
																[(m_board->getBoardPawn(move.first).getCoordY() + m_board->getBoardPawn(move.second).getCoordY()) / 2];
					
					// the middle is enemy pawn
					if (possibleEnemyPawn.getColor() != m_board->getBoardPawn(move.first).getColor() && possibleEnemyPawn.getColor() != "Empty")
					{
						order += 1; ///> make it 5
					}
					// the middle is enemy king
					if (possibleEnemyPawn.isKing() && possibleEnemyPawn.getColor() != m_board->getBoardPawn(move.first).getColor())
					{
						order += 2; ///> make it 6
					}
				}
			}
			else ///> if pawn to move is not a king
			{
				// if pawn to move can jump and the other pawn is a king
				if (order == 4)
				{
					auto possibleEnemyPawn = m_board->getBoard()[(m_board->getBoardPawn(move.first).getCoordX() + m_board->getBoardPawn(move.second).getCoordX()) / 2]
																[(m_board->getBoardPawn(move.first).getCoordY() + m_board->getBoardPawn(move.second).getCoordY()) / 2];
					// the middle is enemy king
					if (possibleEnemyPawn.isKing())
					{
						order += 3; ///> make it 7
					}
				}
			}

			// populate the map
			moveOrders.insert({ order, move });
		});

		// the maximum element | the most swift move of all in the set of possible movements
		auto maxOrderValue = moveOrders.rbegin()->first;

		if (maxOrderValue > 2)
		{
			// do a reasonable move
			// order values for such: 3,4,5,6,7
			// 3 - move a king
			// 4 - take a pawn with a pawn
			// 5 - take a pawn with a king
			// 6 - take a king with a king
			// 7 - take a king with a pawn
			auto maxOrderMove = moveOrders.crbegin()->second;
			Position fromPos = maxOrderMove.first;
			Position toPos = maxOrderMove.second;
			// do movement
			move(fromPos, toPos);
		}
		else
		{
			// do a random move (no other option left)
			// order value for such: 2
			randomMove(possibleMoves);
		}
	}

} } }