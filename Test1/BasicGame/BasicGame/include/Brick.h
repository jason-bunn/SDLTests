#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>
#include "Vector2.h"

class Brick
{
private:
	Vector2		position;

	SDL_Rect	collider;
	SDL_Renderer *ren;

	bool		isAlive;


public:
	void		Init(SDL_Renderer *renderer, Vector2 pos);

	void		Render();
	void		Update();

	void		OnCollision();
};

#endif