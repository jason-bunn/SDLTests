#ifndef BETWEEN_LEVEL_STATE_H
#define BETWEEN_LEVEL_STATE_H

#include "GameState.h"

class BetweenLevelState  : public GameState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;
};


#endif