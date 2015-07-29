#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "SDLGameObject.h"
#include "Level.h"
#include <vector>

//forward declaration
class GameObject;

class PlayState : public GameState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	Level* pLevel;

private:

	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};

#endif