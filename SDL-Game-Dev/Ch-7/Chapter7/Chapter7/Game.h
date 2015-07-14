#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"

class Game
{
public:
	
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void handleEvents();
	void update();
	void quit();
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

	int getGameWidth() const { return m_gameWidth; }
	int getGameHeight() const { return m_gameHeight; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:

	Game();
	static Game* s_pInstance;
	int m_gameWidth;
	int m_gameHeight;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;

	bool m_bRunning;

	GameStateMachine* m_pGameStateMachine;

	std::vector<SDLGameObject*> m_gameObjects;
};
typedef Game TheGame;
#endif