#include "InputManager.h"

bool InputManager::m_mouseIsPressed = bool();

int2 InputManager::m_mouseCoor = int2();

const Uint8* InputManager::m_keyboardState = nullptr;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::setMouseMultiply(float2 multyplier)
{
	m_mouseMultiply.x = multyplier.x;
	m_mouseMultiply.y = multyplier.y;
}

void InputManager::handleInput()
{
	m_mouseIsPressed = false;

	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));

			m_mouseCoor.x *= m_mouseMultiply.x;
			m_mouseCoor.y *= m_mouseMultiply.y;

			break;
		case SDL_MOUSEBUTTONDOWN:
			if (m_event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseIsPressed = true;
			}
			break;
		case SDL_TEXTINPUT:
			m_textInput += m_event.text.text;
			break;

		case SDL_KEYDOWN:
			switch (m_event.key.keysym.sym) 
			{
			case SDLK_BACKSPACE:
				if (!m_textInput.empty()) 
				{
					int lastCharStart = m_textInput.size() - 1;

					while (lastCharStart > 0 && (m_textInput[lastCharStart] & 0xC0) == 0x80) 
					{
						lastCharStart--;
					}
					m_textInput.erase(lastCharStart, m_textInput.size() - lastCharStart);
				}
				break;
			default:
				break;
			}
			break;
		}
	}

	SDL_StartTextInput();

	m_keyboardState = SDL_GetKeyboardState(NULL);
}

bool InputManager::isMousePressed()
{
	return m_mouseIsPressed;
}

bool isAnyKeyPressed()
{
	int numOfKeys = 322;

	for (int i = 0; i < numOfKeys; i++)
	{
		if (InputManager::m_keyboardState[i])
		{
			return true;
		}
	}

	return false;
}

bool isKeyPressed(SDL_Scancode code)
{
	static bool previousState[SDL_NUM_SCANCODES] = { false };
	bool currentState = InputManager::m_keyboardState[code];

	if (currentState && !previousState[code]) 
	{
		previousState[code] = true;
		return true;
	}
	else if (!currentState && previousState[code]) 
	{
		previousState[code] = false;
	}

	return false;
}

string InputManager::getInputData()
{
	if (m_inputData != "")
	{
		string returnValue = m_inputData;
		m_inputData.clear();

		return returnValue;
	}

	return m_inputData;
}

void InputManager::startTextInput()
{
	SDL_StartTextInput();

	m_textInput = "";

	m_textInputIsActive = true;
}

void InputManager::stopTextInput()
{
	SDL_StopTextInput();

	m_textInputIsActive = false;
}

string InputManager::getTextInput()
{
	return m_textInput;
}

void InputManager::resetText(string reset)
{
	if (reset == "0")
	{
		reset = "";
	}
	m_textInput = reset;
}