#include "GameOverState.h"
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "GameObject.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "StateParser.h"
#include <iostream>


const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	std::cout << "entering GameOverSTate" << std::endl;
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}


	std::cout << "exiting GameOverState" << std::endl;
	return true;
}

void GameOverState::update()
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

void GameOverState::render()
{
	if (m_gameObjects.empty())
	{
		return;
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != 0)
		{
			m_gameObjects[i]->draw();
		}
	}
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//if they are of type MenuButton, then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}