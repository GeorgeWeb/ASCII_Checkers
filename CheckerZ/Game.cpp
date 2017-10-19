// project includes
#include "Game.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	// TODO: CREATE A CMake ASAP !!!
	// TODO: SetState as a template function for all StateTypes

	using namespace API;
	using namespace Events;
	using namespace Entity::Player;

	Game::Game() :
		m_title("<A GAME OF CHEKERS>")
	{ }

	Game::~Game()
	{ 
		// TODO: free memory:
		// board pointers in entities
		// each entity
	}

	void Game::begin()
	{
		// initialise the players' data
		m_player1 = std::make_shared<Player>("Black");
		m_player2 = std::make_shared<Player>("Red");
		// adding pointer to the game board for each player in order to control the movement over it.
		m_player1->setBoard(&m_gameBoard);
		m_player2->setBoard(&m_gameBoard);

		// populate the game board with data/pawns
		m_gameBoard.populate();

		// start the game loop
		setGameState(GameSystemState::RUN);
		// let the game loop know that it's the first turn
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
		
		uint8  posKey = '\0'; uint16 posVal = 0;
		switch (ch)
		{
		case static_cast<const char>(GameplayState::MOVE) :
				std::cout << "Enter position: ";
				std::cin >> posKey >> posVal;
				EventManager::getInstance().moveEntityPawn(m_player1, 2, {{ posKey, posVal }});
				setTurnState(TurnState::END);
				break;
			case static_cast<const char>(GameplayState::TAKE) :
				//EventManager::getInstance().takeEntityPawn(m_player2, 3);
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
		m_gameBoard.display();
		// tell the game loop to continue (step in the update func)
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