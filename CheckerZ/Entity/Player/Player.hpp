#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	class Player : public Entity
	{
	public:
		Player(const std::string& t_color);
		~Player() = default;

		void movePawn(const uint16 t_pawnIdx, const vec2 &t_pos) override;
		void takePawn(const uint16 t_pawnIdx) override;
	};

} } }

#endif !PLAYER_HPP