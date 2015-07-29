#ifndef ENEMY_H
#define ENEMY_H

#include "ShooterObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
public:

	virtual std::string type() { return "Enemy"; }

protected:

	int m_health;

	Enemy() : ShooterObject() {}
	virtual ~Enemy() {}
	
};
/*class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};*/

#endif