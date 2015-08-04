#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Camera.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete (*it);
	}
	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

	//iterate through the objects
	if (!m_gameObjects.empty())
	{
		for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			if ((*it)->getPosition().getX() <= TheCamera::Instance()->getPosition().m_x + TheGame::Instance()->getGameWidth())
			{
				(*it)->setUpdating(true);
				(*it)->update();
			}
			else
			{
				if ((*it)->type() != std::string("Player"))
				{
					(*it)->setUpdating(false);
				}
				else
				{
					(*it)->update();
				}
			}

			//check if dead or off screen
			if ((*it)->dead() || (*it)->getPosition().getY() > TheGame::Instance()->getGameHeight())
			{
				std::cout << "deleting";
				delete *it;
				it = m_gameObjects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}