#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

//callbacks
void MainMenuState::s_menuToPlay()
{
	
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->clean(); 
}

//end callbacks