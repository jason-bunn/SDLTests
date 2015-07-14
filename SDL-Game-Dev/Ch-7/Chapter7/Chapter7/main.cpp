#include <iostream>
#include <SDL.h>

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
int g_flags = 0;



int main(int, char**)
{
	Uint32 frameStart, frameTime;

	std::cout << "game init attemp..." << std::endl;
	if (TheGame::Instance()->init("Chapter 3", 100, 100, 640, 480, g_flags))
	{
		std::cout << "Game init success" << std::endl;
		//main loop
		while (TheGame::Instance()->isRunning())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
			
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << std::endl;
		return -1;
	}
	std::cout << "Game closing" << std::endl;
	
	
	return 0;
}