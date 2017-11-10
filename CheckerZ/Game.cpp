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
		//m_player2(std::make_shared<Player>("Player2", "Red")),
		m_player2(std::make_shared<MediumAI>("NormBot", "Red")),
		m_moveGenerator(std::make_shared<MovesGenerator>())
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
				delayHelper(1.0);
				EventManager::getInstance().entityPawnAction(entityOnTurn, m_moveGenerator);

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

			// insert first move on empty undo stack - always
			if (EventManager::getInstance().undoStack.empty())
				EventManager::getInstance().undoStack.push({ fromPos, toPos });

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
						Movement doMove;
						try
						{
							doMove = EventManager::getInstance().handleState({ fromPos, toPos });
						}
						catch (const std::exception& t_excep)
						{
							clearDraw();
							Logger::message(MessageType::ERR, "\t      ", t_excep.what(), EndingDelimiter::NLINE);
						}

						EventManager::getInstance().entityPawnAction(entityOnTurn, doMove.first, doMove.second, m_moveGenerator);

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
						Movement undoedMove = EventManager::getInstance().handleState({/*Empty*/}, GameHistoryState::UNDO);
						fromPos = undoedMove.first;
						toPos = undoedMove.second;

						// call undo function
						undoHelper(entityOnTurn, fromPos, toPos);

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
					clearDraw();
					Logger::message(MessageType::ERR, "\t      Redoing", std::to_string(EventManager::getInstance().redoStack.size()), EndingDelimiter::NLINE);
					while (!EventManager::getInstance().redoStack.empty())
					{
						auto redo = EventManager::getInstance().redoStack.top();
						auto redoFirst = std::to_string(redo.first.first) + std::to_string(redo.first.second);
						auto redoSecond = std::to_string(redo.second.first) + std::to_string(redo.second.second);
						Logger::message(MessageType::ERR, "\t      ", redoFirst + redoSecond, EndingDelimiter::NLINE);
						EventManager::getInstance().redoStack.pop();
					}
					try
					{
						Movement redoedMove = EventManager::getInstance().handleState({ }, GameHistoryState::REDO);
						fromPos = redoedMove.first;
						toPos = redoedMove.second;

						auto tempPawn = m_gameBoard->getBoardPawn(fromPos.first, fromPos.second);
						m_gameBoard->getBoardPawn(fromPos.first, fromPos.second) = m_gameBoard->getBoardPawn(toPos.first, toPos.second);
						m_gameBoard->getBoardPawn(toPos.first, toPos.second) = tempPawn;

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
		//Logger::message(MessageType::INF, "Type: ", t_entity->getClassType() + " |", EndingDelimiter::NONE);
	}

	void Game::initMovesGenerator(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator, std::shared_ptr<Entity::Entity>& t_entity)
	{
		//Logger::message(MessageType::INF, "Possible moves: ", std::to_string(m_moveGenerator->getPossibleMoves().size()));
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

	void Game::undoHelper(std::shared_ptr<Entity::Entity>& t_entityOnTurn, Position fromPos, Position toPos)
	{
		// swapping
		auto tempPawn = m_gameBoard->getBoardPawn(toPos.first, toPos.second);
		m_gameBoard->getBoardPawn(toPos.first, toPos.second) = m_gameBoard->getBoardPawn(fromPos.first, fromPos.second);
		m_gameBoard->getBoardPawn(fromPos.first, fromPos.second) = tempPawn;

		// undo again to get to my turn
		if (EventManager::getInstance().undoStack.size() > 1)
		{
			Movement undoedMove = EventManager::getInstance().handleState({}, GameHistoryState::UNDO);
			fromPos = undoedMove.first;
			toPos = undoedMove.second;

			// swapping
			auto tempPawn = m_gameBoard->getBoardPawn(toPos.first, toPos.second);
			m_gameBoard->getBoardPawn(toPos.first, toPos.second) = m_gameBoard->getBoardPawn(fromPos.first, fromPos.second);
			m_gameBoard->getBoardPawn(fromPos.first, fromPos.second) = tempPawn;

			m_moveGenerator->reset(m_gameBoard, t_entityOnTurn->getPawnColor(), t_entityOnTurn->getLastPlayedPawn());
			// swap entities' turn states
			if (!t_entityOnTurn->getLastPlayedPawn() || m_moveGenerator->getPossibleMoves().empty())
			{
				swapEntityTurns(t_entityOnTurn);
			}
			m_moveGenerator->clear();
		}
		m_moveGenerator->reset(m_gameBoard, t_entityOnTurn->getPawnColor(), t_entityOnTurn->getLastPlayedPawn());
		// swap entities' turn states
		if (!t_entityOnTurn->getLastPlayedPawn() || m_moveGenerator->getPossibleMoves().empty())
		{
			swapEntityTurns(t_entityOnTurn);
		}
		m_moveGenerator->clear();
	}

	void Game::redoHelper(std::shared_ptr<Entity::Entity>& t_entityOnTurn, Position fromPos, Position toPos)
	{

	}
	
	void Game::delayHelper(double maxDelayTime)
	{
		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<double> dist(1.0, maxDelayTime);
		auto delayTime = dist(engine);
		Utils::Timer::applyTimeDelayInSeconds(delayTime);
	}
}