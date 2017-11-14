#include "AI.hpp"

namespace CheckerZ { namespace Entity { namespace AI {

	void EasyAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);
		
		auto possibleMoves = t_moveGenerator->getPossibleMoves();

		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return;

		// do a random move
		randomMove(possibleMoves);
	}

} } }