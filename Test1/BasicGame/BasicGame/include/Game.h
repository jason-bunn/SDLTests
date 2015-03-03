#ifndef GAME_H
#define GAME_H
#include <SDL.h>

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game{
private:
	bool			exitGame;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*brickTex;
	
	Ball			ball;
	Paddle			paddle;
	Brick			bricks[3][11];

public:
					Game();
					~Game();

	bool			Init();
	void			Run();
	void			Update();
	void			CheckCollisions();
	void			CheckColFlags(int&, SDL_Rect, SDL_Rect);
	bool			AABB(SDL_Rect ball, SDL_Rect other);
	void			Render();
	void			ProcessEvents(const SDL_Event &e);
	void			ProcessInput();
	void			CleanupResources();

	void			LogSDLError(std::ostream &os, const std::string &msg);
};

#endif