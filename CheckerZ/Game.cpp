#include "Game.hpp"

#include <iostream>
#include <string>

namespace CheckerZ
{
	Game::Game() 
		: m_gameBoard(std::make_unique<Board>())
	{ }

	Game::~Game()
	{ }

	void Game::Begin()
	{
		// CREATE THE GAME BOARD
		m_gameBoard->populate();
		// START THE GAME LOOP
		m_isRunning = true;
		// DO THE FIRST BOARD DRAW
		Draw();
	}

	void Game::End()
	{
		// EXIT THE GAME LOOP ON WIN CONDITION
		bool win = false;
		if(win) m_isRunning = false;
	}

	void Game::Update()
	{
		// GAME/AI LOGIC IN HERE
		unsigned char ch;
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

	void Game::Draw()
	{
		// RENDERING IS DONE IN HERE
		system("cls");
		std::cout << "\n\n\n\n\t\t\t\t\t       <A GAME OF CHEKERS>";
		m_gameBoard->display();
		m_nextTurn = false;
	}
}