#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H


#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	virtual void update();
	virtual void draw();
	virtual void clean();

private:

	int m_animSpeed;
	int m_numFrames;
};

#endif