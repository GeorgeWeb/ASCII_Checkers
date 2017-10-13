// project includes
#include "Game.hpp"

// std::includes
#include <iostream>

void Run(CheckerZ::Game &t_game);

int main()
{
	CheckerZ::Game game;
	Run(game);

	return EXIT_SUCCESS;
}

void Run(CheckerZ::Game &t_game)
{
	t_game.Begin();

	while (t_game.getIsRunning())
	{
		t_game.Update();

		if (t_game.getNextTurn())
		{
			t_game.Draw();
		}
		
		t_game.End();
	}
}