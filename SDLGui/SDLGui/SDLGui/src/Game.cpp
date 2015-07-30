#include "Game.h"
#include "SDL_timer.h"
#include "FontManager.h"
#include "GuiBox.h"
#include <iostream>

Game* Game::s_pInstance = 0;

GuiBox* badBox;

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
	badBox = new GuiBox(10, 10, 200, 200, { 255, 255,255 });

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

	badBox->draw();
	//display game stats
	displayGameStats();
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
	FNTManager::Instance()->clean();

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::displayGameStats()
{
	int fps = (m_FrameCount / (float)(SDL_GetTicks() - m_StartTime)) * 1000;
	
	if (m_bDisplayStats)
	{
		FNTManager::Instance()->drawText("anon", 600, 100, "FPS: ");
		FNTManager::Instance()->drawText("anon", 700, 100, std::to_string(fps));

	}
}

void Game::loadFonts()
{
	FNTManager::Instance()->loadFont("AnonymousPro.ttf", "anon", 14);
}