#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <random>

#include "Vector2.h"

class Ball
{
private:
	std::string		imageFileName;
	
	SDL_Texture		*ball;
	SDL_Renderer	*renderer;
	
	Vector2			position;
	Vector2			velocity;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> dist;

	SDL_Rect		collider;


public:
	void			Init(SDL_Renderer *ren);
	void			Render();
	void			Update();

	void			OnCollision();
	SDL_Rect		GetColliderBounds() { return collider; }
};
#endif