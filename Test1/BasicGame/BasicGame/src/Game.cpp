#include <SDL.h>
#include <iostream>
#include "Game.h"




Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
	bool success = true;
	//Initialize SDL Resources

	
	return success;
}

void Game::Run()
{
	exitGame = false;
	//Main game loop
	while (!exitGame)
	{
		//debug only
		exitGame = true;
	}
	std::cout << "Exit condition reached" << std::endl;
	SDL_Delay(2000);
	CleanupResources();
	SDL_Quit();
}

void Game::ProcessEvents()
{
	//Process system related events
}

void Game::ProcessInput()
{
	//Process user input
}

void Game::Render()
{

}

void Game::Update()
{

}

void Game::CleanupResources()
{
	//Cleanup all SDL resources used
}