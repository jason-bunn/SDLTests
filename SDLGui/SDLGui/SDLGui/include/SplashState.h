#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <iostream>
#include <vector>
#include "GameState.h"
#include "SDL.h"

class SplashState : public GameState
{
public:

	virtual ~SplashState(){}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_splashID; }

private:

	Uint32 m_timeSinceStart;
	Uint32 m_currentTime;

	float m_alpha;
	int m_secondsToDisplay;

	static const std::string s_splashID;

};


#endif