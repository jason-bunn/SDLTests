#include "Camera.h"
#include "Game.h"

Camera* Camera::s_pInstance = new Camera();

Camera::Camera() : m_pTarget(0), m_position(0, 0)
{

}

Camera::~Camera()
{
	delete m_pTarget;
}

const Vector2D Camera::getPosition() const
{
	if (m_pTarget != 0)
	{
		Vector2D pos(m_pTarget->getX() - (TheGame::Instance()->getGameWidth() / 2), 0);

		if (pos.getX() < 0)
		{
			pos.setX(0);
		}

		return pos;
	}

	return m_position;
}

void Camera::update(Vector2D velocity)
{
	m_position += velocity;

	if (m_position.getX() < 0)
	{
		m_position.setX(0);
	}
}