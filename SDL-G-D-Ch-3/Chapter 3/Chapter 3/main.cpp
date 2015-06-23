#include <iostream>
#include <SDL.h>

#include "Game.h"
int g_flags = 0;

Game* g_game = 0;

int main(int, char**)
{
	g_game = new Game();

	if (g_game->init("Chapter 2", 100, 100, 800, 600, g_flags) == false)
	{
		std::cout << "Failed to initialize game";
		return -1;
	}

	//main loop
	while (g_game->isRunning())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();

		SDL_Delay(10);
	}

	g_game->clean();
	return 0;
}