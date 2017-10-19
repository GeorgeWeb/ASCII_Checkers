#ifndef EVENT_FACTORY_HPP
#define EVENT_FACTORY_HPP

#include "EventImpl/events.h"

namespace CheckerZ { namespace API { namespace Events {

	#pragma region EVENT ENUM CLASSES
	// comment...
	enum class GameSystemState : uint8
	{
		RUN,  ///> non-callable
		WIN,
		LOSE,
		QUIT,
	};
	// comment...
	enum class GameplayState : uint8
	{
		MOVE = 1,
		TAKE = 2
	};
	#pragma endregion

	class EventFactory final
	{
		public:
			// templated body prototype
			template<class StateType>
			static Event create(const StateType& t_state) { }

			template<>
			static Event create<GameSystemState>(const GameSystemState& t_state)
			{
				switch (t_state)
				{
					case GameSystemState::WIN:
						return std::make_shared<EventImpl::WinGame>();
						break;
					case GameSystemState::LOSE:
						return std::make_shared<EventImpl::LoseGame>();
						break;
					case GameSystemState::QUIT:
						return std::make_shared<EventImpl::QuitGame>();
						break;
				}
			}

			template<>
			static Event create<GameplayState>(const GameplayState& t_state)
			{
				switch (t_state)
				{
					case GameplayState::MOVE:
						return std::make_shared<EventImpl::MoveEntityPawn>();
						break;
					case GameplayState::TAKE:
						return std::make_shared<EventImpl::TakeEntityPawn>();
						break;
				}
			}
	};

} } }

#endif !EVENT_FACTORY_HPP