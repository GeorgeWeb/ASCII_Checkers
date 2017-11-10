// project includes
#include "Game.hpp"
#include "API/Utils/Timer.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	// TODO: CREATE A CMake ASAP !!!
	// TODO: SetState as a template function for all StateTypes

	using namespace API;
	using namespace Utils;
	using namespace Events;
	using namespace Entity::Player;
	using namespace Entity::AI;

	Game::Game() :
		m_title("Checkers"),
		m_gameBoard(std::make_shared<Board>()),
		m_player1(std::make_shared<Player>("Gecata", "Black")),
		m_player2(std::make_shared<MediumAI>("NormBot", "Red")),
		m_moveGenerator(std::make_shared<MovesGenerator>())
	{ }

	Game::~Game() { }

	void Game::begin()
	{
		// populate the game board with data(squares)
		m_gameBoard->populate();
		
		// push the board to the undo stack on start
		m_undoStack.push(m_gameBoard->getBoard());

		// adding pointer to the game board for each player in order to control the movement over it.
		m_player1->setBoard(m_gameBoard);
		m_player2->setBoard(m_gameBoard);

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
		
		displayEntityData(entityOnTurn);
		initMovesGenerator(m_moveGenerator, entityOnTurn);
		if (entityOnTurn->getClassType() == "AI")
		{
			try
			{
				// apply delay before taking action
				delayHelper(1.0);

				// invoke the entityPawnAction event that moves the chosen pawn
				EventManager::getInstance().entityPawnAction(entityOnTurn, m_moveGenerator);
				
				// push the current board in the undo stack on every move
				m_undoStack.push(m_gameBoard->getBoard());
				// clear the redo stack
				std::stack<Board::board<Pawn, Board::s_boardLen>>().swap(m_redoStack);

				m_moveGenerator->reset(m_gameBoard, entityOnTurn->getPawnColor(), entityOnTurn->getLastPlayedPawn());
				// swap entities' turn states
				if (!entityOnTurn->getLastPlayedPawn() || m_moveGenerator->getPossibleMoves().empty())
				{
					swapEntityTurns(entityOnTurn);
				}
				m_moveGenerator->clear();

				// Set next turn
				setTurnState(TurnState::END);
			}
			catch (const std::exception& t_excep)
			{
				clearDraw();
				Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
			}
		}
		else
		{
			// read the input for movement/action:
			Logger::message(MessageType::INF, "\t      Command:", EndingDelimiter::SPACE);
			// init readers & read from input
			std::string command = "";
			std::cin >> command;
			// input command correctness check
			if (command.size() > 4)
			{
				clearDraw();
				Logger::message(MessageType::INF, "\t      Invalid input. Try again(4 chars: e.g. MOVE or UNDO or REDO!");
				return;
			}

			// readers for input Position pairs
			uint8 keyFrom{ '\0' }, keyTo{ '\0' };
			uint32 valueFrom{ 0 }, valueTo{ 0 };

			command[0] = islower(command[0]) ? toupper(command[0]) : command[0];
			if (toupper(command[0]) == 'M')
			{
				std::cin >> keyFrom >> valueFrom >> keyTo >> valueTo;
				// discard any case sensitivity ...
				keyFrom = islower(keyFrom) ? toupper(keyFrom) : keyFrom;
				keyTo = islower(keyTo) ? toupper(keyTo) : keyTo;
				// check if input's in the valid character and numeric boundary
				if (keyFrom < 'A' || keyFrom > 'H' || valueFrom < 1 || valueTo > 8)
				{
					clearDraw();
					// read the input for movement/action:
					Logger::message(MessageType::INF, "\t      Invalid input. Try again (A-H and 1-8)!");
					return;
				}
			}

			// save the input in Position pairs
			Position&& fromPos{ keyFrom - 'A', valueFrom - 1 };
			Position&& toPos{ keyTo - 'A' , valueTo - 1 };

			// capitalize command (for case sensitivity purposes)
			for (auto& cmd : command) cmd = toupper(cmd);
			// do action based on command
			switch (command[0])
			{
				default:
					clearDraw();
					Logger::message(MessageType::ERR, "\t      Unkown command.");
				break;
				// TRY MOVEMENT
				case 'M':
					try
					{
						// invoke the entityPawnAction event that moves the chosen pawn
						EventManager::getInstance().entityPawnAction(entityOnTurn, fromPos, toPos, m_moveGenerator);
						
						// push the current board in the undo stack on every move
						m_undoStack.push(m_gameBoard->getBoard());
						// clear the redo stack
						std::stack<Board::board<Pawn, Board::s_boardLen>>().swap(m_redoStack);

						m_moveGenerator->reset(m_gameBoard, entityOnTurn->getPawnColor(), entityOnTurn->getLastPlayedPawn());
						// swap entities' turn states
						if (!entityOnTurn->getLastPlayedPawn() || m_moveGenerator->getPossibleMoves().empty())
						{
							swapEntityTurns(entityOnTurn);
						}
						m_moveGenerator->clear();

						// Set next turn
						setTurnState(TurnState::END);
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
					}
				break;
				// TRY UNDO
				case 'U':
					try
					{
						// call undo helper function
						undoHelper();
					
						// Set next turn
						setTurnState(TurnState::END);
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
					}
				break;
				// TRY REDO
				case 'R':
					try
					{
						// call redo helper function
						redoHelper();

						// Set next turn
						setTurnState(TurnState::END);
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
					}
				break;
			}
		}
	}

	void Game::draw()
	{
		clearDraw();
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

	void Game::displayEntityData(std::shared_ptr<Entity::Entity>& t_entity)
	{
		Logger::message(MessageType::INF, "\t      ", t_entity->getName() + " |", EndingDelimiter::NONE);
		Logger::message(MessageType::INF, "Color: ", t_entity->getPawnColor()/* + " |"*/, EndingDelimiter::NLINE);
	}

	void Game::initMovesGenerator(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator, std::shared_ptr<Entity::Entity>& t_entity)
	{
		m_moveGenerator->generatePossibleMoves(m_gameBoard, t_entity->getPawnColor());
		
		if (m_moveGenerator->getPossibleMoves().empty())
		{
			// ----------- //
			// LOSE / WIN //
			// ---------- //
			m_gameState = GameSystemState::WIN;
			return;
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

	// Game helpers definition/implementation
	void Game::undoHelper()
	{
		if (m_undoStack.size() > 2)
		{
			// create temp board
			Board::board<Pawn, Board::s_boardLen> tempBoard;

			// save the current state of the board in the redo stack
			m_redoStack.push(m_undoStack.top());
			
			// remove it from the undo stack before display
			m_undoStack.pop();
			m_undoStack.pop();
			
			// copy the board from the undo stack into the temp board
			tempBoard = m_undoStack.top();
			
			// copy the temp board into the game board
			m_gameBoard->setBoard(tempBoard);
		}
		else
		{
			throw std::logic_error("There's nothing to undo.");
		}
	}

	void Game::redoHelper()
	{
		if(m_redoStack.size() > 0)
		{ 
			// create temp board
			Board::board<Pawn, Board::s_boardLen> tempBoard;

			// copy the board from the redo stack into the temp board
			tempBoard = m_redoStack.top();

			// save the current state of the board in the undo stack
			m_undoStack.push(m_redoStack.top());

			// copy the temp board into the game board
			m_gameBoard->setBoard(tempBoard);

			// remove it from the redo stack after display
			m_redoStack.pop();
		}
		else
		{
			throw std::logic_error("There's nothing to redo.");
		}
	}
	
	void Game::delayHelper(double t_maxDelayTime)
	{
		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<double> dist(1.0, t_maxDelayTime);
		auto delayTime = dist(engine);
		Utils::Timer::getInstance().applyTimeDelayInSeconds(delayTime);
	}

}