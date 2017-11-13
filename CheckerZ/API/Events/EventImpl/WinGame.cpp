#include "WinGame.hpp"
#include <iostream>

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
		Utils::Logger::message(Utils::MessageType::INF, "\t      Do you want to replay this game ? (y/n):", Utils::EndingDelimiter::SPACE);
		char ch;
		std::cin >> ch;

		if (ch == 'y' || ch == 'Y')
		{

			Utils::Logger::message(Utils::MessageType::INF, "\t      It's ok. You can do better next time!\n");
			// TODO: ... replay it
			system("pause");
		}
		else if(ch == 'n' || ch == 'N')
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Pff.. ignorant prick!\n");
			// TODO: ... ask if he/she wants to start a new game
			system("pause");
		}
		else
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Oh.. ok, anyway you still lost!\n");
			// TODO: ... just clear and tell him it was a wrong answer
			system("pause");
		}
	}

} } } }