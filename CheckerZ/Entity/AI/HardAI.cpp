#include "AI.hpp"
#include <limits>

namespace CheckerZ { namespace Entity { namespace AI {

	void HardAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);

		// minimax algorithm (with alpha-beta cutoffs)

		auto possibleMoves = t_moveGenerator->getPossibleMoves();
	}

	void HardAI::scoredMove(Position& t_fromPos, Position& t_toPos, int32 t_score)
	{

	}

	Movement* HardAI::minimax(std::deque<Movement> t_validMovesList, uint32 t_depth, bool t_isMax)
	{
		// add alpha-beta prunning later (TODO!!!) //
		float alpha = -INFINITY;
		float beta  =  INFINITY;
		// -------------------------------------- //

		// get all valid/possible moves in from the generator
		auto possibleMoves = t_validMovesList;

		//	  add heuristics later (TODO!!!)	//
		auto heuristics = std::deque<Movement>();
		// ------------------------------------ //

		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return nullptr;

		return new Movement;
	}

} } }