#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	class Player : public Entity
	{
	public:
		Player();
		~Player() = default;

		void move(const vec2& t_pos) override;
		void take(const vec2& t_pos) override;
	};

} } }

#endif !PLAYER_HPP