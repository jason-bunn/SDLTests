#ifndef SHOOTER_OBJECT_H
#define SHOOTER_OBJECT_H

#include "GameObject.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject() {}
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented
	virtual std::string type() { return "SDLGameObject"; }

protected:
	//we don't directly create shooter objects
	ShooterObject();

	//draw the animation for the object being destroyed
	void doDyingAnimation();

	//how fast will this object fire bullets? with a counter
	int m_bulletFiringSpeed;
	int m_bulletCounter;

	//how fast will this object move
	int m_moveSpeed;

	//how long does the death animation take? with counter
	int m_dyingTime;
	int m_dyingCounter;

	//has the explosion sound played
	bool m_bPlayedDeathSound;
private:
};


#endif