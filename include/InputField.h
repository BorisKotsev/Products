#pragma once

#include "IFade.h"

#include "Writer.h"

class InputField : public IFade
{
public:
	InputField();
	virtual ~InputField();

	void init(string configFile, string folder);
	void destroy();

	string getValue();

	void readInput();
	void stopInput();

	void update();
	void draw();

	void setWriter(Writer* writer);
	void setText(string text);

	bool readsInput();

	SDL_Rect getRect();
private:

	string m_value;
	string m_displayText;

	SDL_Renderer* m_renderer;

	bool m_readInput;

	SDL_Rect m_rect;

	Drawable m_textUI;

	Writer* m_writer;
};