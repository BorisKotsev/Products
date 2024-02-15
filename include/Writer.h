#pragma once

#include "defines.h"

using namespace std;

class Writer
{
public:

	Writer();
	Writer(SDL_Renderer* renderer);
	~Writer();

	SDL_Renderer* m_renderer;

	pair<int2, SDL_Texture*> getText(string text, FONT fontName, COLOR colorName, int fontSize);

	void init(string config);

private:
	map<int, TTF_Font*> m_font;
	map<COLOR, SDL_Color> m_colors;

	string m_fontLocation;
};