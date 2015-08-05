#include "GuiBox.h"
#include "Game.h"
#include "TextureManager.h"

GuiBox::GuiBox(int x, int y, int width, int height, SDL_Color color)
{
	std::cout << "Creating GUI Box" << std::endl;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_boxColor = color;
	m_borderWidth = 20;

	m_verticalTiles = (m_height / m_borderWidth);
	m_horizontalTiles = (m_width / m_borderWidth);

	//set bg rect
	m_bgRect.x = x + m_borderWidth/2;
	m_bgRect.y = y + m_borderWidth/2;
	m_bgRect.w = width - m_borderWidth;
	m_bgRect.h = height - m_borderWidth;

	//load the texture to use
	std::cout << "Loading Texture" << std::endl;
	TexManager::Instance()->load("assets/images/redBorder2.png", "redBorder", TheGame::Instance()->getRenderer());
	TexManager::Instance()->load("assets/images/bgtest.png", "bgtest", TheGame::Instance()->getRenderer());
}

void GuiBox::draw()
{

	//draw background texture
	
	TexManager::Instance()->draw("bgtest", m_bgRect.x, m_bgRect.y, m_bgRect.w, m_bgRect.h, TheGame::Instance()->getRenderer());


	//draw top left
	TexManager::Instance()->drawFrame("redBorder", m_x, m_y, m_borderWidth, m_borderWidth, 0, 4, TheGame::Instance()->getRenderer(), 0, 255);
	//draw top bar
	TexManager::Instance()->drawHRepeatedFrame("redBorder", m_x + (m_borderWidth), m_y, m_borderWidth, m_borderWidth, 0, 0, TheGame::Instance()->getRenderer(), 0, 255, m_width - (m_borderWidth * 2));


	//draw top right
	TexManager::Instance()->drawFrame("redBorder", m_x + (m_width - m_borderWidth), m_y, m_borderWidth, m_borderWidth, 0, 5, TheGame::Instance()->getRenderer(), 0, 255);
	//draw right vertical
	TexManager::Instance()->drawVRepeatedFrame("redBorder", m_x + (m_width - m_borderWidth), m_y + (m_borderWidth), m_borderWidth, m_borderWidth, 0, 1, TheGame::Instance()->getRenderer(), 0, 255, m_height - (m_borderWidth * 2),SDL_FLIP_HORIZONTAL);
	//draw bottom right
	TexManager::Instance()->drawFrame("redBorder", m_x + (m_width - m_borderWidth), m_y + (m_height - m_borderWidth), m_borderWidth, m_borderWidth, 0, 3, TheGame::Instance()->getRenderer(), 0, 255);
	//draw bottom bar
	TexManager::Instance()->drawHRepeatedFrame("redBorder", m_x + (m_borderWidth), m_y + (m_height - m_borderWidth), m_borderWidth, m_borderWidth, 0, 0, TheGame::Instance()->getRenderer(), 0, 255, m_width - (m_borderWidth * 2), SDL_FLIP_VERTICAL);
	//draw bottom left
	TexManager::Instance()->drawFrame("redBorder", m_x, m_y + (m_height - m_borderWidth), m_borderWidth, m_borderWidth, 0, 2, TheGame::Instance()->getRenderer(), 0, 255);
	//draw left vertical
	//for (int i = 1; i < m_verticalTiles - 1; i++)
	TexManager::Instance()->drawVRepeatedFrame("redBorder", m_x, m_y + (m_borderWidth), m_borderWidth, m_borderWidth, 0, 1, TheGame::Instance()->getRenderer(), 0, 255, m_height - (m_borderWidth * 2));

	
}