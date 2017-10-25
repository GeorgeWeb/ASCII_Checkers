#include "EntityPawnAction.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	EntityPawnAction::EntityPawnAction()
	{

	}

	void EntityPawnAction::initialize()
	{

	}

	void EntityPawnAction::invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2& t_posFrom, vec2&& t_posTo) const
	{
		bool pawnActionResult = t_entity->firePawnAction(t_posFrom, std::move(t_posTo));

		if (!pawnActionResult)
		{
			throw std::runtime_error("Action failed due to an invalid input.");
		}
	}

} } } }