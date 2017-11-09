#ifndef EVENT_FACTORY_HPP
#define EVENT_FACTORY_HPP

#include "EventImpl/events.h"

namespace CheckerZ { namespace API { namespace Events {

	enum class GameSystemState
	{
		RUN,  ///> non-callable
		ACTION,
		WIN,
		QUIT,
	};

	class EventFactory final
	{
		public:
			static Event create(const GameSystemState& t_state)
			{
				switch (t_state)
				{
					case GameSystemState::ACTION:
						return std::make_shared<EventImpl::EntityPawnAction>();
						break;
					case GameSystemState::WIN:
						return std::make_shared<EventImpl::WinGame>();
						break;
					case GameSystemState::QUIT:
						return std::make_shared<EventImpl::QuitGame>();
						break;
				}
			}
	};

} } }

#endif !EVENT_FACTORY_HPP