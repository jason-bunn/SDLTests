#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include <iostream>
#include "ShooterObject.h"
#include "LoaderParams.h"


class ScrollingBackground :public ShooterObject
{
public:
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:

	int count;
	int maxcount;

	SDL_Rect m_srcRect1;
	SDL_Rect m_destRect1;

	SDL_Rect m_srcRect2;
	SDL_Rect m_destRect2;

	int m_scrollSpeed;

	int m_srcRect1Width;
	int m_srcRect2Width;

	int m_destRect1Width;
	int m_destRect2Width;
	
};

#endif