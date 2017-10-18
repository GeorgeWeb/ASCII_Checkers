// project includes
#include "Game.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	using namespace API;
	using namespace Events;
	using namespace Entity::Player;

	Game::Game() :
		m_title("<A GAME OF CHEKERS>"),
		m_gameBoard(std::make_unique<Board>())
	{ }

	Game::~Game()
	{ }

	void Game::begin()
	{
		m_gameBoard->populate();
		setGameState(GameSystemState::RUN);
		
		// TODO: initialise players ...
		m_player = std::make_shared<Player>();
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
				//vec2 newPos = { 'D', 1 }; ///> must be the exact position to place a pawn
				//EventManager::getInstance().moveEntity(m_player, newPos);
				setTurnState(TurnState::END);
				break;
			case static_cast<const char>(GameplayState::TAKE) :
				//EventManager::getInstance().takeEntityPawn(entity);
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
		if (m_gameState == GameSystemState::QUIT)
		{
			// invoke the event that exits the game loop!
			EventManager::getInstance().quitGame();
		}
		else
		{
			switch (m_gameState)
			{
				// Ask if the player wants to exit the game
				// and set the m_gameState to GameSystemState::QUIT
				case GameSystemState::WIN:
					EventManager::getInstance().winGame();
					// temp:
					setGameState(GameSystemState::QUIT);
					break;
				case GameSystemState::LOSE:
					EventManager::getInstance().loseGame();
					// temp:
					setGameState(GameSystemState::QUIT);
					break;
			}
		}
	}
}