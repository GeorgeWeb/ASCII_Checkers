// project includes
#include "Game.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	Game::Game() 
		: m_gameBoard(std::make_unique<Board>())
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
		uchar ch;
		std::cout << "1 - MOVE\n2 - TAKE\n";
		std::cout << "Enter choice: ";
		std::cin >> ch;
		
		switch (ch)
		{
			case static_cast<char>(Gameplay::MOVE):
				std::cout << "I am moving..." << std::endl;
				m_nextTurn = true;
				break;
			case static_cast<char>(Gameplay::TAKE):
				std::cout << "I am taking..." << std::endl;
				m_nextTurn = true;
				break;
			default:
				std::cout << "That's not a valid command, dawg... WTF?" << std::endl;
				break;
		}
	}

	void Game::draw()
	{
		// clear screen after every turn
		system("cls");
		// TODO: add to Title function
		std::cout << "\n\n\n\n\t\t\t\t\t       <A GAME OF CHEKERS>";

		m_gameBoard->display();
		m_nextTurn = false;
	}
}