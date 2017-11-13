// project includes
#include "Game.hpp"

using namespace CheckerZ;
using namespace CheckerZ::API::Utils;

#pragma region HELPERS DECLARATIONS

// simulate the game loop
void runGame(Game& t_game);
// loads game data from a save file into the current game object
void CheckerZ::loadGame(Game& t_game);

#pragma endregion

auto main(void) -> int32
{
	std::string choice;
	Logger::message(MessageType::ERR, "(LOAD an existing game) OR (START a new one) - (load/start):", EndingDelimiter::SPACE);
	std::cin >> choice;
	
	for (auto& ch : choice) ch = toupper(ch);	
	if (choice == "LOAD")
	{
		Game game;
		loadGame(game);
		//runGame(game);
		std::string filePath = ""; std::cin >> filePath;
	}
	else if (choice == "START")
	{	
		Game game;
		game.setTitle("<A GAME OF CHECKERS>");
		runGame(game);
	}
	else
	{
		Logger::message(MessageType::ERR, "Error: you have typed an invalid command.");
	}

	return EXIT_SUCCESS;
}

#pragma region HELPERS DEFINITIONS

void runGame(Game& t_game)
{
	// create game board and assign players
	t_game.begin();

	// Game Loop!
	while (t_game.getIsRunning())
	{
		// update the frames (game movement)
		t_game.update();

		// switch players and re-draw board each turn
		if (t_game.getNextTurn())
		{
			// do the rendering (draw in console)
			t_game.draw();
		}

		// check for win condition & exit the loop
		t_game.end();
	}
}

void CheckerZ::loadGame(Game& t_game)
{
	std::vector<char> gameBoardData;
	API::Events::EventManager::getInstance().loadGame(gameBoardData);
	t_game.setTitle("<A GAME OF CHECKERS>");

	for (auto data : gameBoardData)
	{
		Logger::message(MessageType::INF, "pawn: " + data);
	}
	
	/*
	CheckerZ::API::Board::board<CheckerZ::API::Pawn, CheckerZ::API::Board::s_boardLen> loadedBoard;

	int i = 0;
	for (size_t row = 0; row < 8; row++)
	{
		for (size_t col = 0; col < 8; col++)
		{
			loadedBoard[row][col].getMesh() = gameBoardData[i];
			i++;
		}
	}
	
	t_game.getGameBoard()->setBoard(loadedBoard);
	*/
}

#pragma endregion