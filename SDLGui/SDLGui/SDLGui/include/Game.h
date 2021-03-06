#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "GameStateMachine.h"
#include "Vector2D.h"

#include <string>
#include <map>

class Game
{
public:
	
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void loadFonts();

	void run();
	void render();
	void update(float deltaTime);
	void handleEvents();
	void clean();

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }


	void displayGameStats();

	bool isRunning() { return m_bRunning; }

	int getGameWidth() { return m_Width; }
	int getGameHeight() { return m_Height; }

	void setPlayerLives(int lives) { m_playerLives = lives; }
	int getPlayerLives() { return m_playerLives; }

private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;
	bool m_bDisplayStats;

	static Game* s_pInstance;
	int m_Width;
	int m_Height;

	std::map<std::string, TTF_Font*> m_FontMap;

	int m_FrameCount;
	Uint32 m_StartTime;

	int m_playerLives;
};

typedef Game TheGame;

#endif