#include "Player.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	using namespace API;

	void Player::firePawnAction(const vec2& t_posFrom, const vec2 &t_posTo)
	{
		// check from board if you only need to translate or translate + erase:
		m_board->translate(t_posFrom, t_posTo);
	}

} } }