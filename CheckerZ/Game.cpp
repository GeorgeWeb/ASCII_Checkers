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
		m_title("Checkers"),
		m_gameBoard(std::make_shared<Board>()),
		m_player1(std::make_shared<Player>("Player1")),
		m_player2(std::make_shared<Player>("Player2"))
	{ }

	Game::~Game()
	{ 
		// TODO: free memory:
		// board pointers in entities
		// each entity
	}

	void Game::begin()
	{
		// populate the game board with data(squares)
		m_gameBoard->populate();

		// adding pointer to the game board for each player in order to control the movement over it.
		m_player1->setBoard(m_gameBoard);
		m_player2->setBoard(m_gameBoard);

		// choose player's pawns color
		m_player1->assignPawns("Black");
		m_player2->assignPawns("Red");

		// Choose first entity to begin
		m_player1->setTurn(true);

		// start the game loop
		setGameState(GameSystemState::RUN);
		// let the game loop know that it's the first turn
		setTurnState(TurnState::FIRST);
	}

	void Game::update()
	{
		// skip update and go to draw after if its the first turn
		if (m_turnState == TurnState::FIRST)
		{
			setTurnState(TurnState::END);
			return;
		}

		// ---------------------- //
		// GAMEPLAY LOGIC IN HERE //
		// ---------------------- //
		std::cout << "\n";
		// get the entity who is on turn
		auto entityOnTurn = m_player1->hasTurn() ? m_player1 : m_player2->hasTurn() ? m_player2 : nullptr;
		if (entityOnTurn == nullptr)
		{
			Logger::message(MessageType::ERR, "\t      There's problem with reckognizing the entity that is on turn.");
			return;
		}
		// print the entity who is on turn
		Logger::message(MessageType::INF, "\t      " + entityOnTurn->getName(), "'s turn!");

		// read the input for movement/action:
		// entity picks the pawn
		Logger::message(MessageType::INF, "\t      Pick command:", EndingDelimiter::SPACE);
		// init readers & read from input
		uint8 key = '\0'; uint16 value = 0;
		std::cin >> key >> value;
		// save the input as a typdef unordered_map
		vec2 fromPos{ key, value };

		// entity chooses an action with the picked pawn
		Logger::message(MessageType::INF, "\t      Action command:", EndingDelimiter::SPACE);
		// reset readers & read again
		key = '\0'; value = 0;
		std::cin >> key >> value;
		// save the input as a typdef unordered_map
		vec2 toPos{ key, value };

		bool canMoveAgain = false;
		// Do the ACTION
		try
		{
			EventManager::getInstance().entityPawnAction(entityOnTurn, fromPos, std::move(toPos));
			canMoveAgain = true;
		}
		catch (const std::exception& t_excep)
		{
			Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
			canMoveAgain = false;
		}
		// manage next turn
		if (canMoveAgain)
		{
			// swap entities' turn states
			swapEntityTurns(entityOnTurn);
			// Set next turn
			setTurnState(TurnState::END);
		}
	}

	void Game::draw()
	{
		printTitle();
		// print the board grid
		m_gameBoard->display();
		// tell the game loop to continue (step in the update func)
		setTurnState(TurnState::BEGIN);
	}

	void Game::end()
	{
		// call quit event if there's a win
		if (m_gameState == GameSystemState::QUIT)
			EventManager::getInstance().quitGame();

		// check game states
		switch (m_gameState)
		{
			// ask if the player wants to exit the game,
			// then set the m_gameState to GameSystemState::QUIT
			case GameSystemState::WIN:
				EventManager::getInstance().winGame();
				setGameState(GameSystemState::QUIT);
				break;
		}
	}

	void Game::swapEntityTurns(const std::shared_ptr<Entity::Entity>& t_entityOnTurn)
	{
		if (t_entityOnTurn->hasTurn() == m_player1->hasTurn())
		{
			m_player2->setTurn(m_player1->hasTurn());
			m_player1->setTurn(!m_player1->hasTurn());
		}
		else
		{
			m_player1->setTurn(m_player2->hasTurn());
			m_player2->setTurn(!m_player2->hasTurn());
		}
	}
}