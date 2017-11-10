#include "AI.hpp"

namespace CheckerZ { namespace Entity { namespace AI {

	void EasyAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);
		
		auto possibleMoves = t_moveGenerator->getPossibleMoves();
		// do a random move
		performRandomMove(possibleMoves);
	}

} } }