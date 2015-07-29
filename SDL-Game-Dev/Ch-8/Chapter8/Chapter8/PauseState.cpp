#include "PauseState.h"
#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
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

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != 0)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	std::cout << "entering PauseState" << std::endl;
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	//clear the texture mapper
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	//reset the mouse button states to false
	TheInputHandler::Instance()->reset();

	std::cout << "exiting PauseState" << std::endl;
	return true;
	
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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