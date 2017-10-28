#include "Player.hpp"

// std::includes
#include <cassert>

namespace CheckerZ { namespace Entity { namespace Player {

	void Player::firePawnAction(const Position& t_posFrom, Position&& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> moveGenerator)
	{
		// search t_posTo in generatePossibleMoves
		// if exists such move variant
		// use board to move to it
		assert(std::is_sorted(moveGenerator->getPossibleMoves().begin(), moveGenerator->getPossibleMoves().end()));
			
		if (std::binary_search(moveGenerator->getPossibleMoves().begin(), moveGenerator->getPossibleMoves().end(),
			std::make_pair(t_posFrom, t_posTo)))
		{
			m_board->move(t_posFrom, std::move(t_posTo));
		}
		else
		{
			throw std::logic_error("Action failed due to the selection of impossible move action.");
		}
	}

} } }