#include <iostream>
#include <SDL.h>

#include "Game.h"
int g_flags = 0;

typedef Game TheGame;

int main(int, char**)
{
	std::cout << "game init attemp..." << std::endl;
	if (TheGame::Instance()->init("Chapter 3", 100, 100, 800, 600, g_flags))
	{
		std::cout << "Game init success" << std::endl;
		//main loop
		while (TheGame::Instance()->isRunning())
		{
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			SDL_Delay(10);
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << std::endl;
		return -1;
	}
	std::cout << "Game closing" << std::endl;
	TheGame::Instance()->clean();
	
	return 0;
}