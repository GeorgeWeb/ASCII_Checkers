#ifndef EVENT_FACTORY_HPP
#define EVENT_FACTORY_HPP

#include "EventImpl/events.h"

namespace CheckerZ { namespace API { namespace Events {

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
					case GameSystemState::LOAD:
						return std::make_shared<EventImpl::LoadGame>();
						break;
					case GameSystemState::SAVE:
						return std::make_shared<EventImpl::SaveGame>();
						break;
					case GameSystemState::QUIT:
						return std::make_shared<EventImpl::QuitGame>();
						break;
				}
			}
	};

} } }

#endif !EVENT_FACTORY_HPP