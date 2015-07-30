#include <iostream>
#include <exception>
#include "Application.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int, char**)
{
	Application app;

	app.setApplicationName("SDL Gui Tests");
	app.setAppDimensions(SCREEN_WIDTH, SCREEN_HEIGHT);

	try 
	{
		app.init();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	app.run();

	return 0;
}