#include "WinGame.hpp"
#include <iostream>
#include "events.h"
#include "../../Utils/Timer.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	WinGame::WinGame() : EventFacility()
	{
		initialize();
	}

	void WinGame::initialize()
	{
		// Setup some values...
	}

	void WinGame::invoke(GameSystemState& t_finalGameState, std::shared_ptr<Board>& t_board, const std::shared_ptr<Entity::Entity>& t_player) const
	{
		Utils::Logger::message(Utils::MessageType::INF, "\t      ", t_player->getPawnColor() + " player - " + t_player->getName() + " won! FOR THE HOOOOORDE!\n");
		Utils::Logger::message(Utils::MessageType::INF, "\t      Do you want to replay this game ? (y/n):", Utils::EndingDelimiter::SPACE);
		char ch;
		std::cin >> ch;

		if (ch == 'y' || ch == 'Y')
		{
			while (t_board->s_boardHistory.size() > 0)
			{
				// create temp board
				Board::board<Pawn, Board::s_boardLen> tempBoard;

				// copy the board from the redo stack into the temp board
				tempBoard = t_board->s_boardHistory.front();
				t_board->s_boardHistory.pop_front();

				system("cls");
				// copy the temp board into the game board
				t_board->setBoard(tempBoard);
				t_board->display();
				Utils::Timer::getInstance().applyTimeDelayInSeconds(1.0);
			}
			Utils::Logger::message(Utils::MessageType::INF, "\t      ", t_player->getPawnColor() + " player - " + t_player->getName() + " won! FOR THE HOOOOORDE!\n");
			Utils::Logger::message(Utils::MessageType::INF, "\n\t      Quitting in 5s.");
			Utils::Timer::getInstance().applyTimeDelayInSeconds(5.0);
			t_finalGameState = GameSystemState::QUIT;
		}
		else if(ch == 'n' || ch == 'N')
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Restart game ? (y/n):", Utils::EndingDelimiter::SPACE);
			char ch;
			std::cin >> ch;

			if (ch == 'y' || ch == 'Y')
			{
				Utils::Logger::message(Utils::MessageType::INF, "\t      The game is about to reset in 5s.");
				Utils::Timer::getInstance().applyTimeDelayInSeconds(5.0);
				// TODO: ... ask if he/she wants to start a new game -> ELSE: call the quitGame event!!!
				API::Board newBoard;
				newBoard.populate();
				t_board->setBoard(newBoard.getBoard());
				t_finalGameState = GameSystemState::RUN;
			}
			else ///> no ...
			{
				Utils::Logger::message(Utils::MessageType::INF, "\n\t      Quitting in 5s.");
				Utils::Timer::getInstance().applyTimeDelayInSeconds(5.0);
				t_finalGameState = GameSystemState::QUIT;
			}
		}
		else
		{
			Utils::Logger::message(Utils::MessageType::INF, "\t      Well, it's your choice mate...\n");
			Utils::Logger::message(Utils::MessageType::INF, "\n\t      Quitting in 5s.");
			Utils::Timer::getInstance().applyTimeDelayInSeconds(5.0);
			t_finalGameState = GameSystemState::QUIT;
		}
	}

} } } }