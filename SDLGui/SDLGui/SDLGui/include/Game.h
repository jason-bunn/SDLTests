#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"

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

	void displayGameStats();

	bool isRunning() { return m_bRunning; }

	int getGameWidth() { return m_Width; }
	int getGameHeight() { return m_Height; }

private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	bool m_bDisplayStats;

	static Game* s_pInstance;
	int m_Width;
	int m_Height;

	std::map<std::string, TTF_Font*> m_FontMap;

	int m_FrameCount;
	Uint32 m_StartTime;

};

typedef Game TheGame;

#endif