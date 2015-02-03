#include <iostream>
#include <SDL.h>
#include <string>
#include "Cleanup.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream&, const std::string&);
SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren = nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(ren);
	const std::string resPath = "assets/";
	SDL_Texture *background = loadTexture("background.bmp", ren);
	
	SDL_Texture *image = loadTexture("image.bmp", ren);
	if (background == nullptr || image == nullptr)
	{
		cleanup(background, image, ren, window);
		SDL_Quit();
		return 1;
	}

	

	int bW, bH;
	
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);

	renderTexture(background, ren, 0, 0);
	renderTexture(background, ren, bW, 0);
	renderTexture(background, ren, 0, bH);
	renderTexture(background, ren, bW, bH);

	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, ren, x, y);


	SDL_RenderPresent(ren);
	SDL_Delay(2000);

	cleanup(background, image, ren, window);
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


	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		
		//Make sure converting went ok too
		if (texture == 0)
		{
			logSDLError(std::cout, "CreateTextureFromSurface");
			
		}
		
	}
	else
	{
		logSDLError(std::cout, "LoadBMP");
	}
	SDL_FreeSurface(loadedImage);
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
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	int err = SDL_RenderCopy(ren, tex, NULL, &dst);
	if (err != 0)
	{
		logSDLError(std::cout, "RenderCopy");
	}
}
