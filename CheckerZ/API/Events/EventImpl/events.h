#ifndef EVENTS_H
#define EVENTS_H

#include "EntityPawnAction.hpp"
#include "WinGame.hpp"
#include "LoadGame.hpp"
#include "SaveGame.hpp"
#include "QuitGame.hpp"

namespace CheckerZ { namespace API { namespace Events {

	enum class GameSystemState
	{
		RUN,  ///> non-callable
		ACTION,
		WIN,
		LOAD,
		SAVE,
		QUIT,
	};

} } }

#endif !EVENTS_H