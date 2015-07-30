#include "FontManager.h"
#include "Game.h"
const char* FONT_PATH = "assets/fonts/";

FontManager* FontManager::s_pInstance = 0;

bool FontManager::loadFont(std::string fileName, std::string id, int size)
{
	TTF_Font *tempFont = TTF_OpenFont(std::string(FONT_PATH + fileName).c_str(), 14);
	if (tempFont == 0)
	{
		std::cout << "Failed to load font " << id << std::endl;
		return false;
	}

	m_fontMap[id] = tempFont;
	return true;
}

void FontManager::drawText(std::string fontID, std::string msg)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surf = TTF_RenderText_Blended(m_fontMap[fontID], msg.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surf);

	SDL_FreeSurface(surf);
	int iW, iH;
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	//the position values will have to change when gui system is created
	//the values should be inherited from the container object
	int x = 800 - (iW * 2);
	int y = 20 + (iH / 2);
	SDL_Rect destRect;

	destRect.x = x;
	destRect.y = y;
	destRect.w = iW;
	destRect.h = iH;

	SDL_RenderCopy(TheGame::Instance()->getRenderer(), texture, NULL, &destRect);
	
	//texture must be destroyed to prevent memory leak. there are performance implications for this
	SDL_DestroyTexture(texture);
}

void FontManager::drawText(std::string fontID, int x, int y, std::string msg)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surf = TTF_RenderText_Blended(m_fontMap[fontID], msg.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surf);

	SDL_FreeSurface(surf);
	int iW, iH;
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	
	SDL_Rect destRect;

	destRect.x = x;
	destRect.y = y;
	destRect.w = iW;
	destRect.h = iH;

	SDL_RenderCopy(TheGame::Instance()->getRenderer(), texture, NULL, &destRect);

	//texture must be destroyed to prevent memory leak. there are performance implications for this
	SDL_DestroyTexture(texture);
}

void FontManager::closeFonts()
{
	TTF_CloseFont(m_fontMap["anon"]);
}