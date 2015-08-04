#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:

	static GameObjectFactory* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}

		return s_pInstance;
	}

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it != m_creators.end())
		{
			delete pCreator;
		}

		m_creators[typeID] = pCreator;

		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "could not find type: " << typeID << std::endl;
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:

	GameObjectFactory() {}
	~GameObjectFactory() {}

	std::map<std::string, BaseCreator*> m_creators;

	static GameObjectFactory* s_pInstance;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif