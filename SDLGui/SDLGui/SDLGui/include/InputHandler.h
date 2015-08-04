/*
* InputHandler.h
* Author: Shaun Mitchell
* Modified by: Jason Bunn
* Last modified Date: 8/4/2015
*/

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	//Create as singleton
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	// init joysticks
	void initializeJoysticks();
	bool josyticksInitialized() const { return m_bJoysticksInitialized; }

	void reset();

	//update and clean the input handler
	void update();
	void clean();

	//keyboard events
	bool isKeyDown(SDL_Scancode key) const;

	//joysticks events
	int getAxisX(int joy, int stick) const;
	int getAxisY(int joy, int stick) const;
	bool getButtonState(int joy, int buttonNumber) const;

	//mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;


private:

	//private constructor/destructor for singleton
	InputHandler();
	~InputHandler();

	InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

	//handle keyboard events
	void onKeyDown();
	void onKeyUp();

	//handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);

	//handle joystick events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	//keyboard specific
	const Uint8* m_keystates;

	//joystick specific
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialized;
	static const int m_joystickDeadZone = 10000;

	//mouse specific
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	const int NUM_MOUSE_BUTTONS = 3;

	//singleton
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;


#endif