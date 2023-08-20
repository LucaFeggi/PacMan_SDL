#include <Sound.hpp>

Sound::Sound()
{
	Intro = Mix_LoadWAV("Sounds/Intro.wav");
	EatFruit = Mix_LoadWAV("Sounds/EatFruit.wav");
	ExtraLife = Mix_LoadWAV("Sounds/ExtraLife.wav");
	PacDeath = Mix_LoadWAV("Sounds/PacDeath.wav");
	GhostDeath = Mix_LoadWAV("Sounds/GhostDeath.wav");
	ScatterGhost = Mix_LoadWAV("Sounds/ScatterGhost.wav");
	Waka = Mix_LoadWAV("Sounds/Waka.wav");
	Mix_Volume(-1, 10);
}

Sound::~Sound()
{
	Mix_FreeChunk(Intro);
	Mix_FreeChunk(EatFruit);
	Mix_FreeChunk(ExtraLife);
	Mix_FreeChunk(PacDeath);
	Mix_FreeChunk(GhostDeath);
	Mix_FreeChunk(ScatterGhost);
	Mix_FreeChunk(Waka);
	Intro = NULL;
	EatFruit = NULL;
	ExtraLife = NULL;
	PacDeath = NULL;
	GhostDeath = NULL;
	ScatterGhost = NULL;
	Waka = NULL;
}
