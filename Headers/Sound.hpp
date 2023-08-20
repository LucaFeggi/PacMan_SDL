#pragma once

#include <SDL_mixer.h>

class Sound
{
	public:
		Sound();
		~Sound();
		void PlayIntro(){Mix_PlayChannel(0, Intro, 0);}
		void PlayEatFruit(){Mix_PlayChannel(1, EatFruit, 0);}
		void PlayExtraLife(){Mix_PlayChannel(2, ExtraLife, 0);}
		void PlayPacDeath(){Mix_PlayChannel(3, PacDeath, 0);}
		void PlayGhostDeath(){Mix_PlayChannel(4, GhostDeath, 0);}
		void PlayScatterGhost(){Mix_PlayChannel(5, ScatterGhost, -1);}
		void StopScatterGhost(){Mix_HaltChannel(5);}
		void PlayWaka(){Mix_PlayChannel(6, Waka, -1);}
		void StopWaka(){Mix_HaltChannel(6);}

	private:
		Mix_Chunk* Intro;
		Mix_Chunk* EatFruit;
		Mix_Chunk* ExtraLife;
		Mix_Chunk* PacDeath;
		Mix_Chunk* GhostDeath;
		Mix_Chunk* ScatterGhost;
		Mix_Chunk* Waka;
};
