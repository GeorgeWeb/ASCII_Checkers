#include "Game.hpp"

#include <iostream>

void Run(CheckerZ::Game &game);

int main(void)
{
	CheckerZ::Game game;
	Run(game);

	return EXIT_SUCCESS;
}

void Run(CheckerZ::Game &game)
{
	game.Begin();

	while (game.getIsRunning())
	{
		game.Update();

		if (game.getNextTurn())
		{
			game.Draw();
		}
		
		game.End();
	}
}