#include "EntityPawnAction.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	EntityPawnAction::EntityPawnAction()
	{

	}

	void EntityPawnAction::initialize()
	{

	}

	void EntityPawnAction::invoke(std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<Utils::MovesGenerator>& moveGenerator)
	{
		// TODO: return value type PawnState so I can manage it better from the Game class
		if (t_entity == nullptr)
		{
			throw std::runtime_error("Action failed due to a problem finding such entity to play the game.");
		}

		try
		{
			t_entity->firePawnAction(moveGenerator);
		}
		catch (const std::exception& t_excep)
		{
			throw std::runtime_error(t_excep.what());
		}
	}

	void EntityPawnAction::invoke(std::shared_ptr<Entity::Entity>& t_entity, const Position& t_posFrom, const Position& t_posTo,
		std::shared_ptr<Utils::MovesGenerator>& moveGenerator)
	{
		// TODO: return value type PawnState so I can manage it better from the Game class

		if (t_entity == nullptr)
		{
			throw std::runtime_error("Action failed due to a problem finding such entity to play the game.");
		}
		
		try
		{
			t_entity->firePawnAction(t_posFrom, t_posTo, moveGenerator);
		}
		catch (const std::exception& t_excep)
		{
			throw std::runtime_error(t_excep.what());
		}
	}

} } } }