#include "Brick.h"

void Brick::Init(SDL_Renderer *renderer, Vector2 pos)
{
	this->ren = renderer;

	//set position
	position.x = pos.x;
	position.y = pos.y;

	//set collider bounds
	collider.w = 64;
	collider.h = 32;

	//mark is alive
	isAlive = true;
}

void Brick::Render()
{
	if (isAlive)
	{

	}
}

void Brick::Update()
{

}

void Brick::OnCollision()
{
	if (isAlive)
	{
		isAlive = false;
	}
}