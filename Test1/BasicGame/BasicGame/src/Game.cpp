
#include <iostream>
#include <string>
#include "Game.h"
#include "Cleanup.h"



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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LogSDLError(std::cout, "SDL_Init");
		return false;
	}
	
	window = SDL_CreateWindow("Basic Game tests", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		LogSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		LogSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return false;
	}

	return success;
}

void Game::Run()
{
	exitGame = false;
	SDL_Event e;
	//Main game loop
	while (!exitGame)
	{
		//process events
		while (SDL_PollEvent(&e))
		{
			ProcessEvents(e);
		}
		
		
	}
	std::cout << "Exit condition reached" << std::endl;
	SDL_Delay(2000);
	CleanupResources();
	SDL_Quit();
}

void Game::ProcessEvents(const SDL_Event &e)
{
	//Process system related events
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			std::cout << "Key press detected" << std::endl;
			exitGame = true;
			break;

		default:
			std::cout << "Key press detected" << std::endl;
			exitGame = true;
			break;
		}

	}
	if (e.type == SDL_QUIT)
	{
		exitGame = true;
	}
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

void Game::LogSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}