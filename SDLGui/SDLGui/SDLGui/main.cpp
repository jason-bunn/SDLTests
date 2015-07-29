#include <iostream>
#include <exception>
#include "Application.h"

int main(int, char**)
{
	Application app;

	app.setApplicationName("SDL Gui Tests");
	app.setAppDimensions(800, 600);

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