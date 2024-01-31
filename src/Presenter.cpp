#include "Presenter.h"
#include "World.h"

extern World world;

SDL_Window* Presenter::m_mainWindow = nullptr;
SDL_Renderer* Presenter::m_mainRenderer = nullptr;
int Presenter::m_SCREEN_WIDTH = 0;
int Presenter::m_SCREEN_HEIGHT = 0;

Writer* Presenter::getWriter()
{
	return m_writer;
}

void Presenter::init()
{
	m_SCREEN_WIDTH = 1920;
	m_SCREEN_HEIGHT = 1080;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	TTF_Init();

	m_mainWindow = SDL_CreateWindow("SDL_Template",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);

	m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	improveRenderer();

	m_writer = new Writer(m_mainRenderer);
	m_writer->init("writer.txt");
}

void Presenter::update()
{

}

void Presenter::draw()
{
	SDL_RenderPresent(m_mainRenderer);

	SDL_RenderClear(m_mainRenderer);
}

void Presenter::drawObject(SDL_Texture* texture)
{
	SDL_RenderCopy(m_mainRenderer, texture, NULL, NULL);
}

void Presenter::drawObject(Drawable& drawable)
{
	SDL_RenderCopy(m_mainRenderer, drawable.texture, NULL, &drawable.rect);
}

void Presenter::drawObject(DrawableSrcRect& drawableSrcRect)
{
	SDL_RenderCopy(m_mainRenderer, drawableSrcRect.texture, &drawableSrcRect.rect, &drawableSrcRect.srcRect);
}

void Presenter::drawObject(DrawableTwoTextures& drawableTwoTextures)
{
	SDL_RenderCopy(m_mainRenderer, drawableTwoTextures.texture, NULL, &drawableTwoTextures.rect);
}

void Presenter::improveRenderer()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	auto desktopWidth = DM.w;
	auto desktopHeight = DM.h;

	float2 mouseMultiply;
	mouseMultiply.x = (double)m_SCREEN_WIDTH / (double)desktopWidth;
	mouseMultiply.y = (double)m_SCREEN_HEIGHT / (double)desktopHeight;

	if (SDL_SetWindowFullscreen(m_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
	{
		cout << "SDL Renderer improve failed!" << SDL_GetError();
	}

	world.m_inputManager.setMouseMultiply(mouseMultiply);

	SDL_RenderSetLogicalSize(m_mainRenderer, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

SDL_Texture* loadTexture(string path)
{
	return LoadTexture(path, Presenter::m_mainRenderer);
}
