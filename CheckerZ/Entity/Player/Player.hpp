#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	class Player : public Entity
	{
	public:
		Player(const std::string& t_name) : Entity(t_name) { };
		~Player() = default;

		void firePawnAction(const vec2& t_posFrom, const vec2 &t_posTo) override;

		
	};

} } }

#endif !PLAYER_HPP