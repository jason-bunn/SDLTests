#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include <string>
#include "Vector2.h"

class Paddle
{
private:
	Vector2			position;
	Vector2			velocity;

	SDL_Renderer	*ren;
	SDL_Texture		*paddle;

	std::string		imageFileName;

	SDL_Rect		collider;
public:
	void			Init(SDL_Renderer *renderer);
	void			Render();
	void			GetInput();
	void			Update();

	SDL_Rect		GetColliderBounds() { return collider; }
};

#endif