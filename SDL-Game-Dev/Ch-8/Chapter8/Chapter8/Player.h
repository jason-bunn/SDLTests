#ifndef PLAYER_H
#define PLAYER_H

#include "ShooterObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:

	Player();
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();
	//void load(const LoaderParams* pParams);
private:
	//handle input
	void handleInput();

	//bring the player back if there are lives left
	void ressurect();

	//handle animation
	void handleAnimation();

	//player can be invulnerable for a time
	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

#endif