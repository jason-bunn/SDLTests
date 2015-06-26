#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <vector>
#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:

	//call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();

	std::vector<GameObject*> m_gameObjects;

	static const std::string s_menuID;
};

#endif