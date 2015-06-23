#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Player::draw(SDL_Renderer* pRenderer)
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_position.setX(m_position.getX() + 1);
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Player::clean()
{

}