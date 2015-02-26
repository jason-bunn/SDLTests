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
	SDL_Texture *brick;

	bool		isAlive;


public:
				//Brick(SDL_Renderer *renderer, Vector2 pos, SDL_Texture * const tex);
	void		Init(SDL_Renderer *renderer, Vector2 pos,  SDL_Texture * const tex);

	void		Render();
	void		Update();

	SDL_Rect	GetColliderBounds();
	void		OnCollision();

	bool		IsAlive() { return isAlive; }
};

#endif