// project includes
#include "Game.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	// TODO: MOVE EVENT STUFF IN EVENT MANAGER CLASS
	// TODO: CALL MORE READLE FUNCTION NAMES HERE INSTEAD OF EVENTS CREATION/INVOKE

	using namespace API;
	using namespace Events;

	Game::Game() :
		m_title("<A GAME OF CHEKERS>"),
		m_gameBoard(std::make_unique<Board>())
	{ }

	Game::~Game()
	{ }

	void Game::begin()
	{
		m_gameBoard->populate();
		setGameState(GameEventState::RUN);
		
		// TODO: initialise players ...
		// get first turn
		setTurnState(TurnState::FIRST);
	}

	void Game::update()
	{
		// Skip update and go to draw after if its the first turn
		if (m_turnState == TurnState::FIRST)
		{
			setTurnState(TurnState::END);
			return;
		}

		// GAMEPLAY LOGIC IN HERE
		uint32 ch;
		Logger::message(MessageType::INF, "1 - MOVE\n2 - TAKE\n", "Enter choice: ");
		std::cin >> ch;
		
		switch (ch)
		{
			case static_cast<const char>(GameplayState::MOVE) :
				EventManager::getInstance().moveEntity();
				setTurnState(TurnState::END);
				break;
			case static_cast<const char>(GameplayState::TAKE) :
				EventManager::getInstance().takeEntityPawn();
				setTurnState(TurnState::END);
				break;
			default:
				Logger::message(MessageType::ERR, "That's not a valid command, dawg... WTF?");
				break;
		}
	}

	void Game::draw()
	{
		printTitle();
		// print the board grid
		m_gameBoard->display();

		setTurnState(TurnState::BEGIN);
	}

	void Game::end()
	{
		if (m_gameState == GameEventState::QUIT)
		{
			// invoke the event that exits the game loop!
			EventManager::getInstance().quitGame();
		}
		else
		{
			switch (m_gameState)
			{
				// Ask if the player wants to exit the game
				// and set the m_gameState to GameEventState::QUIT
				case GameEventState::WIN:
					EventManager::getInstance().winGame();
					// temp:
					setGameState(GameEventState::QUIT);
					break;
				case GameEventState::LOSE:
					EventManager::getInstance().loseGame();
					// temp:
					setGameState(GameEventState::QUIT);
					break;
			}
		}
	}
}