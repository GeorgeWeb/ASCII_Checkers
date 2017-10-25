#ifndef PLAYER_HPP
#define PLAYER_HPP

// project includes
#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	class Player : public Entity
	{
	public:
		Player(const std::string& t_name) : Entity(t_name) { };
		~Player() = default;

		bool firePawnAction(const vec2& t_posFrom, vec2&& t_posTo) override;
	};

} } }

#endif !PLAYER_HPP