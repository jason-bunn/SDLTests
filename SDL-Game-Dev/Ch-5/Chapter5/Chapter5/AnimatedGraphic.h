#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H


#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	virtual void update();
private:

	int m_animSpeed;
	int m_numFrames;
};

#endif