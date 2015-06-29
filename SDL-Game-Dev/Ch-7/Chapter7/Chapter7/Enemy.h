#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:

	Enemy();
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
	void load(const LoaderParams* pParams);

private:

	
};
class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};

#endif