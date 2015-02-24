#include <iostream>


#include "Ball.h"


void Ball::Init(SDL_Renderer *ren)
{
	this->renderer = ren;

	imageFileName = "assets/ball.png";

	//load the ball image onto a texture
	ball = IMG_LoadTexture(renderer, imageFileName.c_str());
	if (ball == nullptr)
	{
		std::cout << "Cannot load " << imageFileName << std::endl;
	}

	position.x = 400;
	position.y = 300;
	
	dist = std::uniform_int_distribution<int>(1, 5);
	
	velocity.x = dist(generator);
	velocity.y = dist(generator);


}

void Ball::Render()
{
	int w, h;
	SDL_QueryTexture(ball, NULL, NULL, &w, &h);

	SDL_Rect dst;
	dst.x = position.x;
	dst.y = position.y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(renderer, ball, NULL, &dst);
}

void Ball::Update()
{
	// update position based on velocity
	position.x += velocity.x;
	position.y += velocity.y;

	

	// if position meets the bounds of the screen, reverse velocity
	// this will be handled by collision checking in the future
	if (position.x >= (800 - 64))
	{
		velocity.x *= -1;
	}
	if (position.x <= 0)
	{
		velocity.x *= -1;
	}
	if (position.y >= (600 - 64))
	{
		velocity.y *= -1;
	}
	if (position.y <= 0)
	{
		velocity.y *= -1;
	}
}