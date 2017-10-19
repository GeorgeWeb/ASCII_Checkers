#include "MoveEntityPawn.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	MoveEntityPawn::MoveEntityPawn()
	{

	}

	void MoveEntityPawn::initialize()
	{

	}

	void MoveEntityPawn::invoke(std::shared_ptr<Entity::Entity> t_entity, const uint16 t_pawnIdx, const vec2 &t_pos) const
	{
		t_entity->movePawn(t_pawnIdx, t_pos);
	}

} } } }