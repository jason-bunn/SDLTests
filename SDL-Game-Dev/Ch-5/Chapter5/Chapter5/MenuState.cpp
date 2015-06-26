#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	if (m_gameObjects.empty())
	{
		return;
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != 0)
		{
			m_gameObjects[i]->update();
		}
		
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	//load our menu button images
	if (!TheTextureManager::Instance()->load("assets/button.png", "playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	//create our button objects with appropriate textures
	GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering MenuState" << std::endl;

	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	std::cout << "exiting MenuState" << std::endl;
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked" << std::endl;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked" << std::endl;
	TheGame::Instance()->quit();
}