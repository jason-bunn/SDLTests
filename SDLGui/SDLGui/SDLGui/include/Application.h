#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>


class Application 
{
public:
	bool init();
	void run();

	void setApplicationName(std::string name) { mAppName = name; }
	void setAppDimensions(const int width, const int height);
	std::string getApplicationName() { return mAppName; }

private:

	int mWidth;
	int mHeight;

	std::string mAppName;
};

#endif