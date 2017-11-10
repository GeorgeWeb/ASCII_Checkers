#ifndef PLAYER_HPP
#define PLAYER_HPP

// project includes
#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	class Player final : public Entity
	{
		public:
			Player(const std::string& t_name, const std::string& t_pawnColor) : Entity(t_name, t_pawnColor) { };
			~Player() = default;
			
			std::string getClassType() override { return std::string("Player"); }

			void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator>& moveGenerator) override;
	};

} } }

#endif !PLAYER_HPP