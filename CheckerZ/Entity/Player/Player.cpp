#include "Player.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	using namespace API;

	void Player::firePawnAction(const vec2& t_posFrom, const vec2 &t_posTo)
	{	
		// check from board if you only need to translate or translate + erase:
		// get the entity's own picked pawn
		auto& myPawn = m_board->getPawnGrid(t_posFrom);
		// get the other pawn picked for action by the entity
		auto& action = m_board->getPawnGrid(t_posTo);
		
		// check if it's this player's turn
		if (myPawn.color == m_pawns[0].color)
		{
			// swap the grid positions
			m_board->swapBoardGrids(myPawn, action);
		}
	}

} } }