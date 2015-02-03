#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Cleanup.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

void logSDLError(std::ostream&, const std::string&);
SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;

	}
	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (ren = nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = "assets/";
	SDL_Texture *background = loadTexture(resPath + "background.png", ren);
	SDL_Texture *image = loadTexture(resPath + "image.png", ren);
	if (background == nullptr || image == nullptr)
	{
		cleanup(background, image, ren, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_RenderClear(ren);

	//Determine how many tiles we'll need to fill the screen
	int xTiles = SCREEN_WIDTH / TILE_SIZE;
	int yTiles = SCREEN_HEIGHT / TILE_SIZE;

	//Draw the tiles by calculating their positions
	for (int i = 0; i < xTiles * yTiles; ++i)
	{
		int x = i % xTiles;
		int y = i / xTiles;
		renderTexture(background, ren, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	}
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, ren, x, y);

	SDL_RenderPresent(ren);
	SDL_Delay(2000);

	cleanup(background, image, ren, window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

/**
* Log and SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msge error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
	SDL_Delay(1000);
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{

	
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

/**
* Draw an SDL_Texture to a SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	int err = SDL_RenderCopy(ren, tex, NULL, &dst);
	if (err != 0)
	{
		logSDLError(std::cout, "RenderCopy");
	}
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}