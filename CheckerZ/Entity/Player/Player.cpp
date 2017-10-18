#include "Player.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	using namespace API;
	using namespace Events;

	Player::Player() : Entity()
	{ }

	void Player::move(const vec2& t_pos)
	{
		m_board.traverse([&](uint16 count) {
			// TODO: Movement logic :)
		});
	}

	void Player::take(const vec2& t_pos)
	{
		m_board.traverse([&](uint16 count) {
			// TODO: Taking a pawn logic :)
		});
	}

} } }