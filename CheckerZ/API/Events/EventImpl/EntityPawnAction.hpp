#ifndef ENTITY_PAWN_ACTION_HPP
#define ENTITY_PAWN_ACTION_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class EntityPawnAction : public EventFacility
	{
		public:
			explicit EntityPawnAction();
			~EntityPawnAction() = default;

			void invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2& t_posFrom, const vec2 &t_posTo) const override;

		private:
			void initialize() override;
	};

} } } }

#endif !ENTITY_PAWN_ACTION_HPP