#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../API/Events/EventManager.hpp"
#include "../API/Board.hpp"

namespace CheckerZ { namespace Entity {
	
	using vec2 = std::array<uint32, 2>;

	class Entity
	{
		public:
			Entity() = default;
			virtual ~Entity() = default;

			virtual void move(const vec2& t_pos) = 0;
			virtual void take(const vec2& t_pos) = 0;
		protected:
			API::Board m_board;			
	};

} }
#endif !ENTITY_HPP