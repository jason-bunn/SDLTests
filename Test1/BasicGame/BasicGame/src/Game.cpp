
#include <iostream>
#include <string>
#include <SDL_image.h>
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

	// initialize ball
	ball.Init(renderer);

	// initialize paddle
	paddle.Init(renderer);

	// intialize bricks
	// load shared texture
	brickTex = IMG_LoadTexture(renderer, "assets/brick.png");
	if (brickTex == nullptr)
	{
		std::cout << "Could not load brick texture" << std::endl;
	}
	else
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 11; col++)
			{
				Vector2 temp;
				temp.x = 48 + (col * 64);
				temp.y = 48 + (row * 32);
				bricks[row][col] = Brick();
				bricks[row][col].Init(renderer, temp, brickTex);
			}
		}
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
		//check collisions
		CheckCollisions();
		

		//handle user input
		ProcessInput();

		// update game objects
		Update();

		// draw stuff to the screen
		Render();
		
		
	}
	std::cout << "Exit condition reached" << std::endl;
	SDL_Delay(1000);
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
	paddle.GetInput();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	// call all render methods
	ball.Render();
	paddle.Render();
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 11; col++)
		{
			
			bricks[row][col].Render();
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	ball.Update();
	paddle.Update();
}

void Game::CheckCollisions()
{
	//run collision checks
	if (AABB(ball.GetColliderBounds(), paddle.GetColliderBounds()))
	{
		ball.OnCollision();
	}
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 11; col++)
		{
			if (AABB(ball.GetColliderBounds(), bricks[row][col].GetColliderBounds()))
			{
				if (bricks[row][col].IsAlive())
				{
					ball.OnCollision();
					bricks[row][col].OnCollision();
				}
				
			}
		}
	}
}

bool Game::AABB(SDL_Rect ball, SDL_Rect other)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//calculate the sides of rect A
	leftA = ball.x;
	rightA = ball.x + ball.w;
	topA = ball.y;
	bottomA = ball.y + ball.h;

	//caluculate the sides of rect B
	leftB = other.x;
	rightB = other.x + other.w;
	topB = other.y;
	bottomB = other.y + other.h;

	//check sides for collision
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// if none of the sides from A are outside of B
	return true;
}

void Game::CleanupResources()
{
	//Cleanup all SDL resources used
}

void Game::LogSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}