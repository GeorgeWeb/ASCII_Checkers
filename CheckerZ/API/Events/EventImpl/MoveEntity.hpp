#ifndef MOVE_ENTITY_HPP
#define MOVE_ENTITY_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class MoveEntity : public EventFacility
	{
		public:
			explicit MoveEntity();
			~MoveEntity() = default;

			void invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2 &t_pos) const override;

		private:
			void initialize() override;
	};

} } } }

#endif !MOVE_ENTITY_HPP