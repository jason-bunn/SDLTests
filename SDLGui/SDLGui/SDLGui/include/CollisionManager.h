#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <iostream>
#include <vector>

class Player;
class GameObject;

class CollisionManager
{
public:

	void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
};

#endif