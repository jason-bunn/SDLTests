#include <SDL_image.h>
#include <iostream>

#include "Paddle.h"

void Paddle::Init(SDL_Renderer *renderer)
{
	this->ren = renderer;

	imageFileName = "assets/paddle.png";

	//load the paddle image into a texture
	paddle = IMG_LoadTexture(ren, imageFileName.c_str());
	if (paddle == nullptr)
	{
		std::cout << "Could not laod " << imageFileName << std::endl;
	}

	//set initial position of paddle
	position.x = 400 - 64;
	position.y = 600 - 64;

	//initialize velocity to zero
	velocity.x = 0;
	velocity.y = 0;

	// set collider box size
	collider.w = 128;
	collider.h = 32;
}

void Paddle::Render()
{
	int w, h;
	SDL_QueryTexture(paddle, NULL, NULL, &w, &h);

	SDL_Rect dst;
	dst.x = position.x;
	dst.y = position.y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, paddle, NULL, &dst);
}

void Paddle::GetInput()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	velocity.x = 0;

	
	//check for left and right key press
	if (keyState[SDL_SCANCODE_LEFT])
	{
		if (position.x > 0)
		{
			velocity.x = -5;
		}
		
	}
	else if (keyState[SDL_SCANCODE_RIGHT])
	{
		if (position.x < 800 - 128)
		{
			velocity.x = 5;
		}
		
	}
}

void Paddle::Update()
{

	position.x += velocity.x;

	collider.x = position.x;
	collider.y = position.y;
}

