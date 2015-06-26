#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), m_animSpeed(animSpeed)
{
	m_numFrames = 2;
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));

	SDLGameObject::update();
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{

}