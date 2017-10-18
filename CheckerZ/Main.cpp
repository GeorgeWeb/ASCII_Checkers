// project includes
#include "Game.hpp"

using namespace CheckerZ;

#pragma region HELPERS DECLARATIONS

// simulate the game loop
void runGame(Game& t_game);

#pragma endregion

auto main(void) -> uint32
{
	runGame(Game());
	
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

#pragma endregion