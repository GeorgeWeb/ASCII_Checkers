// project includes
#include "Game.hpp"
#include "API/Utils/Timer.hpp"

// std::includes
#include <iostream>
#include <string>

namespace CheckerZ
{
	using namespace API;
	using namespace Utils;
	using namespace Events;
	using namespace Entity::Player;
	using namespace Entity::AI;

	#pragma region Friend helper functions definition/implementation
	void readInput(Game& t_game, std::string& t_command, uint8& t_keyFrom, uint8& t_keyTo, uint32& t_valueFrom, uint32& t_valueTo)
	{
		// read the input for movement/action:
		Logger::message(MessageType::INF, "\t      Command:", EndingDelimiter::SPACE);
		std::cin >> t_command;

		// input command correctness check
		if (t_command.size() > 4)
		{
			t_game.clearDraw();
			Logger::message(MessageType::INF, "\t      Invalid input. Try again(e.g. - start with move.");
			return;
		}

		t_command[0] = islower(t_command[0]) ? toupper(t_command[0]) : t_command[0];
		if (toupper(t_command[0]) == 'M')
		{
			std::cin >> t_keyFrom >> t_valueFrom >> t_keyTo >> t_valueTo;
			// discard any case sensitivity ...
			t_keyFrom = islower(t_keyFrom) ? toupper(t_keyFrom) : t_keyFrom;
			t_keyTo = islower(t_keyTo) ? toupper(t_keyTo) : t_keyTo;
			// check if input's in the valid character and numeric boundary
			if (t_keyFrom < 'A' || t_keyFrom > 'H' || t_valueFrom < 1 || t_valueTo > t_game.m_gameBoard->s_boardLen)
			{
				t_game.clearDraw();
				// read the input for movement/action:
				Logger::message(MessageType::INF, "\t      Invalid input. Try again (A-H and 1-8).");
				return;
			}
		}

		// capitalize command (for case sensitivity purposes)
		for (auto& cmd : t_command) cmd = toupper(cmd);
	}

	void saveGame(Game& t_game)
	{
		std::vector<char> serializableData;

		// push board data in a buffer
		std::vector<char> boardData;
		std::for_each(t_game.getGameBoard()->getBoard().begin(), t_game.getGameBoard()->getBoard().end(), [&](auto grid)
		{
			std::for_each(grid.cbegin(), grid.cend(), [&](auto pawn)
			{
				boardData.push_back(pawn.getMesh());
			});
		});
		serializableData.insert(serializableData.end(), boardData.begin(), boardData.end());

		// push players state in a buffer
		std::vector<char> playersData;
		std::copy(t_game.m_redPlayer->getName().begin(), t_game.m_redPlayer->getName().end(), std::back_inserter(playersData));
		std::copy(t_game.m_blackPlayer->getName().begin(), t_game.m_blackPlayer->getName().end(), std::back_inserter(playersData));
		serializableData.insert(serializableData.end(), playersData.begin(), playersData.end());

		// call save game event for all data sets / buffers
		EventManager::getInstance().saveGame(serializableData, "savedGame.check");
	}
	#pragma endregion

	Game::Game() :
		m_title("Checkers"),
		m_gameBoard(std::make_shared<Board>()),
		m_moveGenerator(std::make_shared<MovesGenerator>())
	{ }

	Game::~Game() { }

	void Game::setRedPlayer(PlayerType t_playerType, double t_speed, const std::string& t_name)
	{
		if (t_playerType == HUMAN)
			m_redPlayer = std::make_shared<Player>();
		else if (t_playerType == EASY_CPU)
			m_redPlayer = std::make_shared<EasyAI>();
		else if (t_playerType == MEDIUM_CPU)
			m_redPlayer = std::make_shared<MediumAI>();
		else if (t_playerType == HARD_CPU)
			m_redPlayer = std::make_shared<HardAI>();
		
		m_redPlayer->setColor("Red");
		if (t_speed != 0.0) m_redPlayer->setSpeed(t_speed);
		if (!t_name.empty()) m_redPlayer->setName(t_name);
	}

	void Game::setBlackPlayer(PlayerType t_playerType, double t_speed, const std::string& t_name)
	{
		if (t_playerType == HUMAN)
			m_blackPlayer = std::make_shared<Player>();
		else if (t_playerType == EASY_CPU)
			m_blackPlayer = std::make_shared<EasyAI>();
		else if (t_playerType == MEDIUM_CPU)
			m_blackPlayer = std::make_shared<MediumAI>();
		else if (t_playerType == HARD_CPU)
			m_blackPlayer = std::make_shared<HardAI>();

		m_blackPlayer->setColor("Black");
		if (t_speed != 0.0) m_redPlayer->setSpeed(t_speed);
		if (!t_name.empty()) m_blackPlayer->setName(t_name);
	}

	void Game::begin()
	{
		// populate the game board with data(squares)
		m_gameBoard->populate();
		
		// push the board to the undo stack on start
		m_undoStack.push(m_gameBoard->getBoard());
		m_gameBoard->s_boardHistory.push_back(m_gameBoard->getBoard());

		// adding pointer to the game board for each player in order to control the movement over it.
		assert(m_redPlayer != nullptr);
		m_redPlayer->setBoard(m_gameBoard);
		assert(m_blackPlayer != nullptr);
		m_blackPlayer->setBoard(m_gameBoard);
		
		// Choose first entity to begin
		m_redPlayer->setTurn(true);

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
		auto entityOnTurn = m_redPlayer->hasTurn() ? m_redPlayer : m_blackPlayer->hasTurn() ? m_blackPlayer : nullptr;
		
		displayEntityData(entityOnTurn);
		initMovesGenerator(m_moveGenerator, entityOnTurn);
		if (entityOnTurn->getClassType() == "AI")
		{
			try
			{
				// apply delay before taking action
				double delayTime = entityOnTurn->getSpeed();
				delayTime = delayTime < 1.0 ? 0.0 : delayTime;
				delayHelper(delayTime);
				// invoke the entityPawnAction event that moves the chosen pawn
				EventManager::getInstance().entityPawnAction(entityOnTurn, m_moveGenerator);
				
				// handle the end of turn						
				endTurn(entityOnTurn, m_moveGenerator);
			}
			catch (const std::exception& t_excep)
			{
				clearDraw();
				Logger::message(MessageType::ERR, "\t      ", t_excep.what());
			}
		}
		else
		{
			// init readers & read from input
			std::string command = "";
			// readers for input Position pairs
			uint8 keyFrom{ '\0' }, keyTo{ '\0' };
			uint32 valueFrom{ 0 }, valueTo{ 0 };

			// read the player input and save it in the above variables
			readInput(*this, command, keyFrom, keyTo, valueFrom, valueTo);
			
			// do action based on command
			switch (command[0])
			{
				default:
					clearDraw();
					Logger::message(MessageType::ERR, "\t      Unkown command.");
					return;
				break;
				// TRY MOVEMENT
				case 'M':
					try
					{
						// save the input in Position pairs
						Position&& fromPos{ keyFrom - 'A', valueFrom - 1 };
						Position&& toPos{ keyTo - 'A' , valueTo - 1 };

						// invoke the entityPawnAction event that moves the chosen pawn
						EventManager::getInstance().entityPawnAction(entityOnTurn, fromPos, toPos, m_moveGenerator);

						// handle the end of turn						
						endTurn(entityOnTurn, m_moveGenerator);
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what());
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
						Logger::message(MessageType::ERR, "\t      ", t_excep.what());
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
						Logger::message(MessageType::ERR, "\t      ", t_excep.what());
					}
				break;
				// TRY SAVE
				case 'S':
					try
					{
						saveGame(*this);
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what());
					}
				break;
				// TRY QUIT/EXIT
				case 'Q':
				case 'E':
					try
					{
						quitHelper();
					}
					catch (const std::exception& t_excep)
					{
						clearDraw();
						Logger::message(MessageType::ERR, "\t      ", t_excep.what());
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
		// check game states
		switch (m_gameState)
		{
			// Try to call the win event and set the m_gameState to GameSystemState::QUIT
			case GameSystemState::WIN:
				try
				{
					GameSystemState finalGameState;
					winHelper(finalGameState);
					setGameState(finalGameState);
				}
				catch (const std::exception& t_excep)
				{
					clearDraw();
					Logger::message(MessageType::ERR, "\t      ", t_excep.what());
				}
			break;
			// Try to call quit event if there's a win
			case GameSystemState::QUIT:
				try
				{
					EventManager::getInstance().quitGame();
				}
				catch (const std::exception& t_excep)
				{
					clearDraw();
					Logger::message(MessageType::ERR, "\t      ", t_excep.what());
				}
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
			setGameState(GameSystemState::WIN);
			return;
		}
	}

	void Game::swapEntityTurns(const std::shared_ptr<Entity::Entity>& t_entityOnTurn)
	{
		// self-explanatory - just swap the hasTurn boolean values of both players
		if (t_entityOnTurn->hasTurn() == m_redPlayer->hasTurn())
		{
			m_blackPlayer->setTurn(m_redPlayer->hasTurn());
			m_redPlayer->setTurn(!m_redPlayer->hasTurn());
		}
		else
		{
			m_redPlayer->setTurn(m_blackPlayer->hasTurn());
			m_blackPlayer->setTurn(!m_blackPlayer->hasTurn());
		}
	}

	void Game::endTurn(const std::shared_ptr<Entity::Entity>& t_entity, std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		// push the current board in the undo stack on every move
		m_undoStack.push(m_gameBoard->getBoard());
		m_gameBoard->s_boardHistory.push_back(m_undoStack.top());

		// clear the redo stack
		std::stack<Board::board<Pawn, Board::s_boardLen>>().swap(m_redoStack);
		
		// CHECK WIN CONDITION
		// check if the next player on turn has lost
		m_moveGenerator->reset(m_gameBoard, t_entity->getPawnColor() == "Red" ? "Black" : "Red", nullptr);

		if (m_moveGenerator->getPossibleMoves().empty())
		{
			// clear the memory from the possible moves container
			m_moveGenerator->clear();
			// set win event
			setGameState(GameSystemState::WIN);
			return;
		}
		else
		{
			// CHECK IF CAN TAKE AGAIN WITH THE SAME PAWN CONDITION
			// check if it possible to continue the turn with the pawn that was played
			m_moveGenerator->reset(m_gameBoard, t_entity->getPawnColor(), t_entity->getLastPlayedPawn());

			// swap entities' turn states
			if (!t_entity->getLastPlayedPawn() || m_moveGenerator->getPossibleMoves().empty())
				swapEntityTurns(t_entity);

			// empty the moves container before ending
			m_moveGenerator->clear();

			// Set next turn
			setTurnState(TurnState::END);
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

			// discard the last moves from the gameHistory queue on undo
			m_gameBoard->s_boardHistory.pop_back();
			m_gameBoard->s_boardHistory.pop_back();
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
			m_undoStack.push(m_redoStack.top());

			// copy the temp board into the game board
			m_gameBoard->setBoard(tempBoard);

			// remove it from the redo stack after display
			m_redoStack.pop();

			// save the moves in the gameHistory deque's back since these are the last current ones
			m_gameBoard->s_boardHistory.push_back(m_undoStack.top());
			m_gameBoard->s_boardHistory.push_back(m_undoStack.top());
		}
		else
		{
			throw std::logic_error("There's nothing to redo.");
		}
	}

	void Game::winHelper(GameSystemState& t_finalGameState)
	{
		// get the entity who is on turn
		auto entityOnTurn = m_redPlayer->hasTurn() ? m_redPlayer : m_blackPlayer->hasTurn() ? m_blackPlayer : nullptr;

		// invoke the winGame event
		EventManager::getInstance().winGame(t_finalGameState, m_gameBoard, entityOnTurn);
	}

	void Game::quitHelper()
	{
		EventManager::getInstance().quitGame();
	}
	
	void Game::delayHelper(double t_maxDelayTime)
	{
		// generate random delayTime number in the range of 0 to the passed argument
		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<double> dist(0.0, t_maxDelayTime);
		auto delayTime = dist(engine);
		Utils::Timer::getInstance().applyTimeDelayInSeconds(delayTime);
	}

}