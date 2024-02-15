#include "Writer.h"

Writer::Writer()
{

}

Writer::Writer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Writer::~Writer()
{

}

pair<int2, SDL_Texture*> Writer::getText(string text, FONT fontName, COLOR colorName, int fontSize)
{
	TTF_Font* font;
	switch (fontName)
	{
	case FONT::FONT:
		font = m_font.at(fontSize);
		break;
	default:
		font = nullptr;
	}
	

	const char* t = text.c_str();

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, t, m_colors.at(colorName));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	int2 size;
	size.x = surface->w;
	size.y = surface->h;

	pair<int2, SDL_Texture*> returnData
		= pair<int2, SDL_Texture*>(size, texture);

	SDL_FreeSurface(surface);

	return returnData;
}

void Writer::init(string configFile)
{
	configFile = CONFIG_FOLDER + configFile;

	m_fontLocation = FONT_FOLDER + "Oswald-Regular.ttf"; //AdventPro-Bold.ttf OpenSans-Regular.ttf DejaVuSans.ttf

	TTF_Font* _font;

	for (int i = 11; i <= 72; i++)
	{
		_font = TTF_OpenFont(m_fontLocation.c_str(), i);
		m_font.insert(pair<int, TTF_Font*>(i, _font));
	}

	SDL_Color color;

	color.a = Uint8(255);
	color.r = Uint8(255);
	color.g = Uint8(255);
	color.b = Uint8(255);

	m_colors.insert(pair<COLOR, SDL_Color>(COLOR::LIGHT, color));

	color.r = Uint8(0);
	color.g = Uint8(0);
	color.b = Uint8(0);

	m_colors.insert(pair<COLOR, SDL_Color>(COLOR::DARK, color));
}