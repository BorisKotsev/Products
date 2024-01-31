#pragma once

#include "Engine.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	static int2 m_mouseCoor;

	static const Uint8* m_keyboardState;

	void handleInput();
	void setMouseMultiply(float2 multyplier);

	static bool isMousePressed();

	string getInputData();
	
	void startTextInput();
	void stopTextInput();
	void resetText(string reset);

	string getTextInput();

private:
	SDL_Event m_event;

	float2 m_mouseMultiply;

	static bool m_mouseIsPressed;

	string m_inputData;
	string m_textInput;

	bool m_textInputIsActive;
};

bool isAnyKeyPressed();

bool isKeyPressed(SDL_Scancode code);