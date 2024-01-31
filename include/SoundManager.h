#pragma once

#include <SDL_mixer.h>

#include "Engine.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void init();
	static void playSound(SOUND sound);
	void destroy();

private:
	static Mix_Chunk* m_backgroundMusic;
};