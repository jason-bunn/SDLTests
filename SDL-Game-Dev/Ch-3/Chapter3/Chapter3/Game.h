#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void handleEvents();
	void update();

	void clean();

	bool isRunning() { return m_bRunning; }

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:

	Game();
	static Game* s_pInstance;
	

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;

	bool m_bRunning;


	std::vector<SDLGameObject*> m_gameObjects;
};

#endif