#include "WinGame.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	WinGame::WinGame() : EventFacility()
	{
		initialize();
	}

	void WinGame::initialize()
	{
		// Setup some values...
	}

	void WinGame::invoke() const
	{
		Utils::Logger::message(Utils::MessageType::INF, "\t      There aren't any possible move variants. You're losing, pal!\n");
		system("PAUSE");
	}

} } } }