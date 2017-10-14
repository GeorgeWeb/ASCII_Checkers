// project includes
#include "Game.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	using API::Logger;
	using API::MessageType;

	Game::Game() 
		: m_gameBoard(std::make_unique<API::Board>())
	{ }

	Game::~Game()
	{ }

	void Game::begin()
	{
		m_gameBoard->populate();
		m_isRunning = true;
		// draw the board (initially)
		draw();
	}

	void Game::end()
	{
		// TODO: Check for win condition (make event system and run on event being invoked)
		bool win = false;
		if(win) m_isRunning = false;
	}

	void Game::update()
	{
		// GAME/AI LOGIC IN HERE
		char ch;
		Logger::message(MessageType::INF, "1 - MOVE\n2 - TAKE\n");
		Logger::message(MessageType::INF, "Enter choice: ");
		std::cin >> ch;
		
		switch (ch)
		{
			case static_cast<const char>(Gameplay::MOVE) :
				Logger::message(MessageType::INF, "I am moving...");
				m_nextTurn = true;
				break;
			case static_cast<const char>(Gameplay::TAKE) :
				Logger::message(MessageType::INF, "I am taking...");
				m_nextTurn = true;
				break;
			default:
				Logger::message(MessageType::ERR, "That's not a valid command, dawg... WTF?");
				break;
		}
	}

	void Game::draw()
	{
		// clear screen after every turn
		system("cls");
		// TODO: add to Title function
		Logger::message(MessageType::INF, "\n\n\n\t\t\t\t\t       <A GAME OF CHEKERS>");

		m_gameBoard->display();
		m_nextTurn = false;
	}
}