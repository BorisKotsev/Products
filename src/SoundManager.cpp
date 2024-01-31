#include "SoundManager.h"

Mix_Chunk* SoundManager::m_backgroundMusic = nullptr;

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::init()
{
	fstream stream;

	string tmp, backgroundMusic;

	stream.open(CONFIG_FOLDER + "soundManager.txt");

	stream >> tmp >> backgroundMusic;

	stream.close();

	//Open the mixer, if there is a problem, prints the error
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + backgroundMusic).c_str());

	//SoundManager::playSound(SOUND::BACKGORUND_MUSIC);
}

void SoundManager::playSound(SOUND sound)
{
	Mix_AllocateChannels(2);//Secure 2 channels for the sounds

	switch (sound)
	{
	case SOUND::BACKGORUND_MUSIC:
		Mix_PlayChannel(0, m_backgroundMusic, -1); //If -1 doesn't work -> 100000
		
		Mix_Volume(0, 50);
		break;
	default:
		cout << "Invalid sound" << endl;
		break;
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = nullptr;
}
