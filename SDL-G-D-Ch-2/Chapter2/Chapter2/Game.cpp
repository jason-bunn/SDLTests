#include "Game.h"
#include "TextureManager.h"

typedef TextureManager TheTextureManager;

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success" << std::endl;
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "Window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				std::cout << "Renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
			}
			else
			{ 
				std::cout << "Renderer init fail" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Window creation fail" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "SDL Init fail" << std::endl;
		return false;
	}

	std::cout << "Everything init OK" << std::endl;

	if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
	{
		return false;
	}

	m_bRunning = true;

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//render stuff here
	TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);
	
	TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	//update all the things!
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Game::clean()
{
	std::cout << "Cleaning up your mess" << std::endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

