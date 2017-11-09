#include "Player.hpp"

// std::includes
#include <cassert>
#include <cmath>

namespace CheckerZ { namespace Entity { namespace Player {

	void Player::firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator)
	{
		// search t_posTo in generatePossibleMoves
		// if exists such move variant
		// use board to move to it
		assert(std::is_sorted(t_moveGenerator->getPossibleMoves().begin(), t_moveGenerator->getPossibleMoves().end()));
		
		if (std::binary_search(t_moveGenerator->getPossibleMoves().begin(), t_moveGenerator->getPossibleMoves().end(),
			std::make_pair(t_posFrom, t_posTo)))
		{
			API::ActionState turnState = m_board->move(t_posFrom, t_posTo);
			
			// if an action has happened -> a pawn with coords: t_posFrom and a pawn with coords: t_posTo will have their values swapped
			if (turnState == API::ActionState::JUMP)
				m_lastPlayedPawn = std::make_shared<API::Pawn>(m_board->getBoardPawn(t_posTo));
			
			if (turnState == API::ActionState::MOVE)
				m_lastPlayedPawn = nullptr;
		}
		else
		{
			throw std::logic_error("Action failed due to the selection of impossible move action.");
		}
	}

} } }