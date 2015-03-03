
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
	int colFlags = 0;
	
	//run collision checks
	
	if (AABB(ball.GetColliderBounds(), paddle.GetColliderBounds()))
	{
		CheckColFlags(colFlags, ball.GetColliderBounds(), paddle.GetColliderBounds());
		//std::cout << colFlags << std::endl;
		ball.OnCollision(colFlags);
	}
	
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 11; col++)
		{
			colFlags = 0;
			//colFlags = AABB(ball.GetColliderBounds(), bricks[row][col].GetColliderBounds());
			if (AABB(ball.GetColliderBounds(), bricks[row][col].GetColliderBounds()))
			{
				if (bricks[row][col].IsAlive())
				{
					CheckColFlags(colFlags, ball.GetColliderBounds(), bricks[row][col].GetColliderBounds());
					ball.OnCollision(colFlags);
					bricks[row][col].OnCollision();
				}
				
			}
		}
	}
}

bool Game::AABB(SDL_Rect ball, SDL_Rect other)
{
	// bottom = 2
	// top = 4
	// left = 8
	// right = 16


	
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	int widthA, widthB;
	//calculate the sides of rect A
	leftA = ball.x;
	rightA = ball.x + ball.w;
	topA = ball.y;
	bottomA = ball.y + ball.h;
	widthA = rightA - leftA;

	//caluculate the sides of rect B
	leftB = other.x;
	rightB = other.x + other.w;
	topB = other.y;
	bottomB = other.y + other.h;
	widthB = rightB - leftB;
	//check sides for collision
	
	//check bottom of ball to top of other
	if (bottomA <= topB)
	{
		return false;
		
	}
	
	if (topA >= bottomB)
	{
		return false;
	}
	
	if (rightA  <= leftB)
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

void Game::CheckColFlags(int& colflags, SDL_Rect ball, SDL_Rect other)
{
	Vector2 ballCenter, otherCenter;
	ballCenter.y = ball.y + (ball.h / 2);
	ballCenter.x = ball.x + (ball.w / 2);

	otherCenter.y = other.y + (other.h / 2);
	otherCenter.x = other.x + (other.w / 2);

	// if the center of the ball is in the width of other
	if (ballCenter.y > other.y && ballCenter.y < (other.y + other.h))
	{
		colflags += 8;
	}
	else
	{
		colflags += 2;
	}
}

void Game::CleanupResources()
{
	//Cleanup all SDL resources used
}

void Game::LogSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}