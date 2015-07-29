#include "Game.h"
#include "SDL_timer.h"

#include <iostream>

Game* Game::s_pInstance = 0;

Game::Game() :
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_bDisplayStats(true)
{
	m_FrameCount = 0;
}

Game::~Game()
{
	m_pRenderer = 0;
	m_pWindow = 0;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	m_Width = width;
	m_Height = height;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Init success" << std::endl;

		//initialize the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "Window creation success" << std::endl;

			//initialize renderer
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer != 0) //success
			{
				std::cout << "Renderer creation success" << std::endl;
				//set draw color
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "Renderer init failed: " << SDL_GetError() << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Window init failed: " << SDL_GetError() << std::endl;
			return false;
		}
		if (TTF_Init() != 0)
		{
			std::cout << "Font init failed: " << SDL_GetError() << std::endl;
			return false;
		}

	}
	else
	{
		std::cout << "SDL Init failed: " << SDL_GetError() << std::endl;
		return false;
	}

	//register sounds and objects
	loadFonts();


	m_bRunning = true;
	return true;
}

//Main Game Loop
void Game::run()
{
	//Frames per second timer setup
	m_StartTime = SDL_GetTicks();
	

	Uint32 old_time, current_time;
	float deltaTime;

	current_time = SDL_GetTicks();

	while (m_bRunning)
	{
		//update delta time
		old_time = current_time;
		deltaTime = (current_time - old_time) / 1000.0f;
		current_time = SDL_GetTicks();
		

		handleEvents();
		update(deltaTime);
		render();

		//increment frame counter
		m_FrameCount++;
	}

	clean();
}

void Game::render()
{
	//clear renderer
	SDL_RenderClear(m_pRenderer);
	
	//render all the things


	//display game stats
	//displayGameStats();
	//display to renderer
	SDL_RenderPresent(m_pRenderer);
}

void Game::update(float deltaTime)
{

}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		}
	}
}

void Game::clean()
{
	std::cout << "Cleaning and exiting" << std::endl;
	
	//close all fonts
	TTF_CloseFont(m_FontMap["StatFont"]);

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::displayGameStats()
{
	int fps = (m_FrameCount / (float)(SDL_GetTicks() - m_StartTime)) * 1000;
	
	std::string fpsMsg = "FPS: " + std::to_string(fps);
	

	SDL_Color color = { 255, 255, 255 };
	if (m_bDisplayStats)
	{
		SDL_Surface *surf = TTF_RenderText_Blended(m_FontMap["StatFont"], fpsMsg.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(m_pRenderer, surf);

		
		int iW, iH;
		SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
		int x = m_Width  - (iW * 2);
		int y = 20 + (iH / 2);
		SDL_Rect destRect;

		destRect.x = x;
		destRect.y = y;
		destRect.w = iW;
		destRect.h = iH;

		SDL_RenderCopy(m_pRenderer, texture, NULL, &destRect);

	}
}

void Game::loadFonts()
{
	TTF_Font *statFont = TTF_OpenFont("assets/fonts/orbitron-light.otf", 14);
	if (statFont == 0)
	{
		std::cout << "Failed to load font" << std::endl;
		return;
	}

	m_FontMap.emplace("StatFont", statFont);
}