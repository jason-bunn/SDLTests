#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"



class FontManager
{
public:

	static FontManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new FontManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool loadFont(std::string fileName, std::string id, int size);
	void drawText(std::string fontID, std::string msg);
	void drawText(std::string fontID, int x, int y, std::string msg);

	void clean();

private:
	FontManager() {}
	~FontManager() {}

	std::map<std::string, TTF_Font*> m_fontMap;

	static FontManager* s_pInstance;
};

typedef FontManager FNTManager;

#endif