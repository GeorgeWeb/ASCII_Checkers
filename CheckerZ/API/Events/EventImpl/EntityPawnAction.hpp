#ifndef ENTITY_PAWN_ACTION_HPP
#define ENTITY_PAWN_ACTION_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class EntityPawnAction : public EventFacility
	{
		public:
			explicit EntityPawnAction();
			~EntityPawnAction() = default;

			void invoke(std::shared_ptr<Entity::Entity> t_entity, const Position& t_posFrom, const Position& t_posTo,
				std::shared_ptr<Utils::MovesGenerator> moveGenerator) override;

		private:
			void initialize() override;
			
	};

} } } }

#endif !ENTITY_PAWN_ACTION_HPP