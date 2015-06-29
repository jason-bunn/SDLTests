#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

Game* Game::s_pInstance = 0;

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
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
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

	TheInputHandler::Instance()->initializeJoysticks();

	std::cout << "Everything init OK" << std::endl;


	//register object types
	GOFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	GOFactory::Instance()->registerType("Player", new PlayerCreator());
	GOFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GOFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	//initialize game state machine and push the menu state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true;

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//render stuff here
	
	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	/*if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}*/
}

void Game::update()
{
	//update all the things!
	m_pGameStateMachine->update();
}

void Game::clean()
{
	std::cout << "Cleaning up your mess" << std::endl;
	TheInputHandler::Instance()->clean();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	
}

void Game::quit()
{
	clean();
	SDL_Quit();
	m_bRunning = false;
}