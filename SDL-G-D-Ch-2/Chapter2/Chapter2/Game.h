#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL_image.h>
#include "SDL.h"

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void handleEvents();
	void update();

	void clean();

	bool isRunning() { return m_bRunning; }
private:

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;

	bool m_bRunning;

};

#endif