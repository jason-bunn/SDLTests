
#include <iostream>
#include <sstream>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "Game.h"
#include "Cleanup.h"

TTF_Font *gFont;

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

	if (TTF_Init() == -1)
	{
		LogSDLError(std::cout, "Error loading TTF");
	}
	// open TTF
	OpenFont();

	return success;
}

void Game::Run()
{
	Uint32 currentTime;
	
	int fps = 0;

	exitGame = false;
	SDL_Event e;

	currentTime = SDL_GetTicks();

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
		Render(currentTime, fps);

		fps++;
		
		
		
	}
	std::cout << "Exit condition reached" << std::endl;
	SDL_Delay(1000);
	CleanupResources();
	TTF_Quit();
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

void Game::Render(Uint32 currentTime, int fps)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
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

	RenderFramesPerSecond(currentTime, fps);

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

void Game::OpenFont()
{
	gFont = TTF_OpenFont("assets/data-latin.ttf", 18);
	if (gFont == nullptr)
	{
		LogSDLError(std::cout, "Open Font Failed");
	}
}

void Game::RenderText(const std::string &msg, SDL_Color color)
{
	SDL_Surface *surf = TTF_RenderText_Solid(gFont, msg.c_str(), color);
	if (surf == nullptr)
	{
		TTF_CloseFont(gFont);
		LogSDLError(std::cout, "TTF_RenderText");
		
	}

	debugText = SDL_CreateTextureFromSurface(renderer, surf);
	if (debugText == nullptr)
	{
		LogSDLError(std::cout, "Create font Texture");
	}

	SDL_FreeSurface(surf);

}

void Game::RenderFramesPerSecond(Uint32 startTime, int fps)
{
	float totalFps = (fps / (float)(SDL_GetTicks() - startTime)) * 1000;

	std::stringstream ss;
	
	ss << totalFps;

	

	std::string fpsText = "FPS: ";
	fpsText.append(ss.str());
	SDL_Color textColor = { 255, 255, 255, 255 };
	// render debug text (fps)
	RenderText(fpsText, textColor);
	SDL_Rect debugRect;

	debugRect.x = 600;
	debugRect.y = 25;
	SDL_QueryTexture(debugText, NULL, NULL, &debugRect.w, &debugRect.h);
	SDL_RenderCopy(renderer, debugText, NULL, &debugRect);
}

