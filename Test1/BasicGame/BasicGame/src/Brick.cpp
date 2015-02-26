#include "Brick.h"

/*Brick::Brick(SDL_Renderer *renderer, Vector2 pos, SDL_Texture * const tex)
{
	this->ren = renderer;
	this->brick = tex;
	//set position
	position.x = pos.x;
	position.y = pos.y;

	//set collider bounds
	collider.w = 64;
	collider.h = 32;

	//mark is alive
	isAlive = true;
}*/

void Brick::Init(SDL_Renderer *renderer, Vector2 pos, SDL_Texture * const tex)
{
	this->ren = renderer;
	this->brick = tex;
	//set position
	position.x = pos.x;
	position.y = pos.y;

	//set collider bounds
	collider.x = position.x;
	collider.y = position.y;
	collider.w = 64;
	collider.h = 32;

	//mark is alive
	isAlive = true;
}

void Brick::Render()
{
	if (isAlive)
	{
		int w, h;
		SDL_QueryTexture(brick, NULL, NULL, &w, &h);

		SDL_Rect dst;
		dst.x = position.x;
		dst.y = position.y;
		dst.w = w;
		dst.h = h;

		SDL_RenderCopy(ren, brick, NULL, &dst);
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

SDL_Rect Brick::GetColliderBounds()
{
	return collider;
}