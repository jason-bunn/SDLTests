#include "SplashState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "MainMenuState.h"

const std::string SplashState::s_splashID = "SPLASH";

bool SplashState::onEnter()
{
	m_alpha = 0.f;
	std::cout << "Entering Splash state" << std::endl;
	m_secondsToDisplay = 2;
	m_timeSinceStart = SDL_GetTicks();
	TexManager::Instance()->load("assets/images/splashship2.png", "splashShip", TheGame::Instance()->getRenderer());
	m_loadingComplete = true;
	return true;
}

bool SplashState::onExit()
{
	m_exiting = true;
	return true;
}

void SplashState::update()
{
	m_currentTime = SDL_GetTicks();
	m_alpha += 1 * (m_currentTime - m_timeSinceStart) /1000;
	if (m_alpha >= 255)
	{
		m_alpha = 255;
	}
	if ((m_currentTime - m_timeSinceStart) / 1000 >= m_secondsToDisplay)
	{
		TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	}
}

void SplashState::render()
{
	//FNTManager::Instance()->drawText("anon", TheGame::Instance()->getGameWidth() / 2, TheGame::Instance()->getGameHeight() / 2, "SPLASH SCREEN");
	TexManager::Instance()->drawAlpha("splashShip", 80, 92, 640, 415, TheGame::Instance()->getRenderer(),(int) m_alpha);
}