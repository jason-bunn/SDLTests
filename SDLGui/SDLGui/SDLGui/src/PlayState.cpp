#include <iostream>
#include "PlayState.h"
//#include "GameOverState.h"
//#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"
#include "TextureManager.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{

}

void PlayState::render()
{

}

bool PlayState::onEnter()
{
	return true;
}

bool PlayState::onExit()
{
	m_exiting = true;

	return true;
}