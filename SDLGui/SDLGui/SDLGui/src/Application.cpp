#include "Application.h"
#include "Game.h"

#include <iostream>

bool Application::init()
{
	std::cout << "Initializing " << getApplicationName() << std::endl;
	if(TheGame::Instance()->init(getApplicationName().c_str(), 50, 50, mWidth, mHeight, false))
	{
		return true;
	}
	return false;
}

void Application::run()
{
	std::cout << "Running " << getApplicationName() << std::endl;
	TheGame::Instance()->run();
}

void Application::setAppDimensions(const int width, const int height)
{
	mWidth = width;
	mHeight = height;
}
