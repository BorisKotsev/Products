#include "World.h"

World::World()
{
	m_isRunning = true;
}

World::~World()
{

}

void World::init()
{
	m_soundManager.init();
	m_presenter.init();
	m_stateManager.init(GAME_STATE::GAME);
}

void World::run()
{
	m_inputManager.handleInput();

	m_stateManager.run();

	m_presenter.draw();
}

void World::destroy()
{
	m_soundManager.destroy();

	SDL_DestroyRenderer(m_presenter.m_mainRenderer);

	SDL_DestroyWindow(m_presenter.m_mainWindow);
}

bool World::isRunning()
{
	return m_isRunning;
}