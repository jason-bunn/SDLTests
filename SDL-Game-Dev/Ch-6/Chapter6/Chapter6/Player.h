#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:

	Player();
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
	void load(const LoaderParams* pParams);
private:

	void handleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

#endif