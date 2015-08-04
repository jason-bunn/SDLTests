#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "Vector2D.h"

class Camera
{
public:

	static Camera* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Camera();
		}

		return s_pInstance;
	}

	void update(Vector2D velocity);

	void setTarget(Vector2D* target) { m_pTarget = target; }
	void setPosition(const Vector2D& position) { m_position = position; }

	const Vector2D getPosition() const;

private:

	Camera();
	~Camera();

	Vector2D* m_pTarget;

	Vector2D m_position;

	static Camera* s_pInstance;
};

typedef Camera TheCamera;


#endif