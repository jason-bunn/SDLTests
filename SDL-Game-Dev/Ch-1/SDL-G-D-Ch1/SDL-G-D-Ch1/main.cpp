#include <iostream>
#include <SDL.h>

#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game* g_game = 0;

const int g_flags = 0;

int main(int argc, char** argv)
{
	
	g_game = new Game();

	g_game->init("Chapter 1", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, g_flags);

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}
	g_game->clean();

	return 0;
}