#ifndef MAIN_MENU_STATE
#define MAIN_MENU_STATE

#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	//call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();

	std::vector<GameObject*> m_gameObjects;

	static const std::string s_menuID;
};

#endif