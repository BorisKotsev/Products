#pragma once

#include "Engine.h"
#include "Writer.h"

class Presenter
{
public:
	static SDL_Window* m_mainWindow;
	static SDL_Renderer* m_mainRenderer;

	Writer* getWriter();

	static int m_SCREEN_WIDTH;
	static int m_SCREEN_HEIGHT;

	void init();
	void update();
	void draw();

	static void drawObject(SDL_Texture* texture);
	static void drawObject(Drawable& drawable);
	static void drawObject(DrawableSrcRect& drawableSrcRect);
	static void drawObject(DrawableTwoTextures& drawableTwoTextures);

private:
	Writer* m_writer;

	void improveRenderer();
};

template <typename Params>
void drawObject(Params& value)
{
	Presenter::drawObject(value);
}

SDL_Texture* loadTexture(string path);