#include "EntityPawnAction.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	EntityPawnAction::EntityPawnAction()
	{

	}

	void EntityPawnAction::initialize()
	{

	}

	void EntityPawnAction::invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2& t_posFrom, const vec2 &t_posTo) const
	{
		t_entity->firePawnAction(t_posFrom, t_posTo);
	}

} } } }