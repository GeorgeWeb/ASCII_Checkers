#include "MoveEntity.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	MoveEntity::MoveEntity()
	{

	}

	void MoveEntity::initialize()
	{

	}

	void MoveEntity::invoke(std::shared_ptr<Entity::Entity> t_entity, const vec2 &t_pos) const
	{
		t_entity->move(t_pos);
	}

} } } }