class Sound{
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

Sound::Sound(){
	Intro = Mix_LoadWAV("Sounds/Intro.wav");
	EatFruit = Mix_LoadWAV("Sounds/EatFruit.wav");
	ExtraLife = Mix_LoadWAV("Sounds/ExtraLife.wav");
	PacDeath = Mix_LoadWAV("Sounds/PacDeath.wav");
	GhostDeath = Mix_LoadWAV("Sounds/GhostDeath.wav");
	ScatterGhost = Mix_LoadWAV("Sounds/ScatterGhost.wav");
	Waka = Mix_LoadWAV("Sounds/Waka.wav");
	Mix_Volume(-1, 10);
}

Sound::~Sound(){
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
