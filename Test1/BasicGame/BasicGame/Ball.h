#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Vector2.h"

class Ball
{
private:
	std::string		imageFileName;
	
	SDL_Texture		*ball;
	SDL_Renderer	*renderer;
	
	Vector2			position;
	Vector2			velocity;


public:
	void			Init(SDL_Renderer *ren);
	void			Render();
	void			Update();
};
#endif