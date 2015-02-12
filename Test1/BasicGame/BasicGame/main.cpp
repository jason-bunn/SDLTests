#include <iostream>
#include <SDL.h>

#include "Game.h"

int main(int, char**)
{
	Game game = Game();

	// if game fails to initialize shut it down
	if (!game.Init())
	{
		std::cout << "Failed to initialize game" << std::endl;
		return -1;
	}
	else
	{
		game.Run();
	}
	return 0;
}