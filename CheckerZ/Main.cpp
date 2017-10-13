// project includes
#include "Game.hpp"

// std::includes
#include <iostream>

// simulate the game loop *Declaration*
void runGame(CheckerZ::Game &t_game);

auto main() -> unsigned int
{
	// PLAY: (the game object's instantiated on the stack)
	runGame(CheckerZ::Game());
	
	// the usual return value '0' for the invoked 'exit()'
	return EXIT_SUCCESS;
}

// simulate the game loop *Definition*
void runGame(CheckerZ::Game &t_game)
{
	// create game board and assign players
	t_game.begin();

	// Game Loop!
	while (t_game.getIsRunning())
	{
		// update the frames (game movement)
		t_game.update();

		// 
		if (t_game.getNextTurn())
		{
			// do the rendering (draw in console)
			t_game.draw();
		}
		
		// check for win condition & exit the loop
		t_game.end();
	}
}