#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:

	MenuButton();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; }

private:

	void(*m_callback)();
	bool m_bReleased;

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	int m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};

#endif