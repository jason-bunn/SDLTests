#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"

class Enemy : public SDLGameObject
{
public:

	Enemy(const LoaderParams* pParams);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
};


#endif