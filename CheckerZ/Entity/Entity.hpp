#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../API/Board.hpp"

namespace CheckerZ { namespace Entity {

	class Entity
	{
		// TODO: Override operator[] to get positiona by using .x/.y instead of [0]/[1]

		public:
			Entity() = default;
			virtual ~Entity() = default;

			virtual void move(const vec2 &t_pos) = 0;
			virtual void take() = 0;

			virtual const vec2 &getPosition() { return m_position; };
		protected:
			vec2 m_position;
	};

} }
#endif !ENTITY_HPP