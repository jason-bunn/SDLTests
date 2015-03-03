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
	
	dist = std::uniform_int_distribution<int>(4, 7);
	
	velocity.x = dist(generator);
	velocity.y = dist(generator);

	//set collider size
	collider.x = position.x;
	collider.y = position.y;
	collider.w = 32;
	collider.h = 32;

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
	if (position.x >= (800 - 32))
	{
		velocity.x *= -1;
	}
	if (position.x <= 0)
	{
		velocity.x *= -1;
	}
	if (position.y >= (600 - 32))
	{
		velocity.y *= -1;
	}
	if (position.y <= 0)
	{
		velocity.y *= -1;
	}

	collider.x = position.x;
	collider.y = position.y;
}

void Ball::OnCollision(int colFlags)
{
	// callback fires on collision with another object
	//std::cout << "Collision detected" << std::endl;
	std::cout << colFlags << std::endl;
	if (colFlags % 2 != 0 || colFlags % 4 != 0)
	{
		velocity.y *= -1;
	}
	else if (colFlags % 8 != 0 || colFlags % 16 != 0)
	{
		velocity.x *= -1;
	}
	
}