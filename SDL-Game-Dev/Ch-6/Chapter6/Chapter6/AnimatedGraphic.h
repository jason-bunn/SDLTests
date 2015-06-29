#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H


#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();

	virtual void update();
	virtual void draw();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:

	
};
class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};
#endif