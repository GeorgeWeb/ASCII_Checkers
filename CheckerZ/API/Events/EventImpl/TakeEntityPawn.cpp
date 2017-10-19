#include "TakeEntityPawn.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	TakeEntityPawn::TakeEntityPawn()
	{

	}

	void TakeEntityPawn::initialize()
	{

	}

	void TakeEntityPawn::invoke(std::shared_ptr<Entity::Entity> t_entity, const uint16 t_pawnIdx) const
	{
		t_entity->takePawn(t_pawnIdx);
	}

} } } }