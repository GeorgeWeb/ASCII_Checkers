#include "WinGame.hpp"
#include <iostream>
#include "events.h"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	WinGame::WinGame() : EventFacility()
	{
		initialize();
	}

	void WinGame::initialize()
	{
		// Setup some values...
	}

	void WinGame::invoke(GameSystemState& t_finalGameState, std::shared_ptr<Board>& t_board) const
	{
		Utils::Logger::message(Utils::MessageType::INF, "\t      There aren't any possible move variants. You're losing, pal!\n");
		Utils::Logger::message(Utils::MessageType::INF, "\t      Do you want to replay this game ? (y/n):", Utils::EndingDelimiter::SPACE);
		char ch;
		std::cin >> ch;

		if (ch == 'y' || ch == 'Y')
		{

			Utils::Logger::message(Utils::MessageType::INF, "\t      It's ok. You can do better next time!\n");
			// TODO: ... replay it
			t_finalGameState = GameSystemState::QUIT;
			system("pause");
		}
		else if(ch == 'n' || ch == 'N')
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Pff.. ignorant prick!\n");
			// TODO: ... ask if he/she wants to start a new game -> ELSE: call the quitGame event!!!
			API::Board newBoard;
			t_board->setBoard(newBoard.getBoard());
			t_board->populate();
			t_finalGameState = GameSystemState::RUN;
		}
		else
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Oh.. ok, anyway you still lost!\n");
			// TODO: ... just clear and tell him it was a wrong answer
			t_finalGameState = GameSystemState::QUIT;
			system("pause");
		}
	}

} } } }