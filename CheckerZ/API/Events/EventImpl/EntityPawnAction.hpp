#ifndef ENTITY_PAWN_ACTION_HPP
#define ENTITY_PAWN_ACTION_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class EntityPawnAction : public EventFacility
	{
		public:
			explicit EntityPawnAction();
			~EntityPawnAction() = default;
			
			// used for AI
			void invoke(std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<Utils::MovesGenerator>& moveGenerator) override final;
			// used for Player
			void invoke(std::shared_ptr<Entity::Entity>& t_entity, const Position& t_posFrom, const Position& t_posTo,
				std::shared_ptr<Utils::MovesGenerator>& moveGenerator) override final;

		private:
			void initialize() override;
			
	};

} } } }

#endif !ENTITY_PAWN_ACTION_HPP