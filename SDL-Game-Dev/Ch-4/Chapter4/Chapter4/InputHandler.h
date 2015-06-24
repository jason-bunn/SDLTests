#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include "SDL.h"
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}
	void initializeJoysticks();
	bool joysticksInitialized() { return m_bJoysticksInitialized; }
	void update();
	void clean();
private:

	InputHandler();
	~InputHandler(){}

	static InputHandler* s_pInstance;

	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialized;

};
typedef InputHandler TheInputHandler;

#endif