#include "ShooterObject.h"

#include "TextureManager.h"
#include "Game.h"


void ShooterObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width,
			m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width,
			m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}

}

void ShooterObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void ShooterObject::doDyingAnimation()
{
	//keep scrolling with the map
	scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++; 
}