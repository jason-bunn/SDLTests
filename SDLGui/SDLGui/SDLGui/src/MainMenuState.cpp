#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "FontManager.h"

const std::string MainMenuState::s_menuID = "MENU";

//callbacks
void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->clean(); 
}

//end callbacks

void MainMenuState::update()
{
	if (m_loadingComplete && !m_gameObjects.empty() && !m_exiting)
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->update();
		}
	}
}

void MainMenuState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
	FNTManager::Instance()->drawText("anon", TheGame::Instance()->getGameWidth() / 2, TheGame::Instance()->getGameHeight() / 2, "MAIN MENU");
}

bool MainMenuState::onEnter()
{
	//parse the state
	//StateParser stateParser;
	//stateParser.parseState("assets/conan.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	//push callbacks
	m_callbacks.push_back(0); //empty callback
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	//set callbacks for menu items

	m_loadingComplete = true;
	std::cout << "Entering Main Menu State" << std::endl;
	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	//clean up game objects
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();

	TheInputHandler::Instance()->reset();

	std::cout << "Exiting Main Menu State" << std::endl;
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through game objects
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			//if there are any GO of type MenuButton, assign a callback based on the id passed in from file
			if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}