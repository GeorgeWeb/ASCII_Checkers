// project includes
#include "Game.hpp"

using namespace CheckerZ;
using namespace CheckerZ::API::Utils;

#pragma region HELPERS DECLARATIONS

// simulate the game loop
void runGame(Game& t_game);
// loads game data from a save file into the current game object
void CheckerZ::loadGame(Game& t_game, const std::string& t_filePath);

#pragma endregion

auto main(void) -> int32
{
	std::string choice;
	Logger::message(MessageType::ERR, "(LOAD an existing game) OR (START a new one) - (load/start):", EndingDelimiter::SPACE);
	std::cin >> choice;
	
	for (auto& ch : choice) ch = toupper(ch);	
	if (choice == "LOAD")
	{
		std::string filePath = "";
		// TODO: ... game set board, etc.
		Game game;
		loadGame(game, filePath);
		runGame(game);
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

void CheckerZ::loadGame(Game& t_game, const std::string& t_filePath)
{
	// API::Events::EventManager::getInstance().loadGame();
	t_game.setTitle("<A GAME OF CHECKERS>");
}

#pragma endregion