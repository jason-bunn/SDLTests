#ifndef GUI_BOX_H
#define GUI_BOX_H

#include "SDL.h"
#include <iostream>

class GuiBox
{
public:

	GuiBox(int x, int y, int width, int height, SDL_Color color);

	void draw();
private:

	SDL_Rect m_bgRect;
	SDL_Color m_boxColor;

	int m_x;
	int m_y;
	int m_borderWidth;
	int m_width;
	int m_height;

	int m_verticalTiles;
	int m_horizontalTiles;
};


#endif