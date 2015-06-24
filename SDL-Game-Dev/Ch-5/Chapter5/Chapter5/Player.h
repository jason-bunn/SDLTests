#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"

class Player : public SDLGameObject
{
public:

	Player(const LoaderParams* pParams);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
	
private:

	void handleInput();
};

#endif