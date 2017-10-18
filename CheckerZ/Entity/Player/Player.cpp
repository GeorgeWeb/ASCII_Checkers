#include "Player.hpp"
#include "../../API/Utils/GameHelper.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	using namespace API;

	Player::Player() : Entity()
	{ }

	void Player::move(const vec2 &t_pos)
	{
		Utils::BoardHelper::traverse([&](uint16 count) {
			// TODO: Movement logic :)
		});
	}

	void Player::take()
	{
		Utils::BoardHelper::traverse([&](uint16 count) {
			// TODO: Taking a pawn logic :)
		});
	}

} } }