#ifndef EVENT_FACTORY_HPP
#define EVENT_FACTORY_HPP

#include "EventFacility.hpp"
#include "Win.hpp"

namespace CheckerZ { namespace API { namespace Events {

	#pragma region EVENT ENUM CLASSES
	// comment...
	enum class GameEventState : uint8
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

	class EventFactory
	{
		public:
			// templated body prototype
			template<class StateType>
			static Event create(const StateType& t_state) { }

			template<>
			static Event create<GameEventState>(const GameEventState& t_state)
			{
				switch (t_state)
				{
					case GameEventState::WIN:
						return std::make_shared<Win>(); ///> class WinGame
						break;
					case GameEventState::LOSE:
						return std::make_shared<Win>(); ///> class LoseGame
						break;
					case GameEventState::QUIT:
						return std::make_shared<Win>(); ///> class QuitGame
						break;
				}
			}

			template<>
			static Event create<GameplayState>(const GameplayState& t_state)
			{
				switch (t_state)
				{
					case GameplayState::MOVE:
						return std::make_shared<Win>(); ///> class MoveEntity
						break;
					case GameplayState::TAKE:
						return std::make_shared<Win>(); ///> class TakeEntityPawn
						break;
				}
			}
	};

} } }

#endif !EVENT_FACTORY_HPP