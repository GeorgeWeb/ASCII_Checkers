#include "AI.hpp"
#include <map>

namespace CheckerZ { namespace Entity { namespace AI {

	void MediumAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);
		
		// Greedy algorithm!!! ...
		std::map<uint32, Movement> moveOrders;
		auto possibleMoves = t_moveGenerator->getPossibleMoves();

		std::for_each(possibleMoves.begin(), possibleMoves.end(), [&](const Movement& move)
		{
			uint32 order = std::abs(static_cast<int>(move.first.first - move.second.first) + std::abs(static_cast<int>(move.first.second - move.second.second)));
			// make order higher if the pawn is a king
			if (m_board->getBoardPawn(move.first).isKing())
			{
				if (m_board->getBoardPawn(move.second).getColor() != m_board->getBoardPawn(move.first).getColor() 
				 && m_board->getBoardPawn(move.second).getColor() != "Empty")
					order += 2;
				else
					order += 1;
			}

			// populate the map
			moveOrders.insert({ order, move });
		});

		// the maximum element | the most swift move of all in the set of possible movements
		auto maxOrderValue = moveOrders.crbegin()->first;

		if (maxOrderValue > 2)
		{
			// do a reasonable move
			auto maxOrderMove = moveOrders.crbegin()->second;
			m_board->move(maxOrderMove.first, maxOrderMove.second);
		}
		else
		{
			// do a random move (no other option left)
			performRandomMove(possibleMoves);
		}
	}

} } }