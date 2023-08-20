#include <Globals.hpp>

#include <SDL_image.h>
#include <SDL_mixer.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect* CurrentClip = NULL;
TTF_Font* Font = NULL;
TTF_Font* LittleFont = NULL;

void InitializeSDL(
    void
) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	TTF_Init();
	Font = TTF_OpenFont("Fonts/emulogic.ttf", BlockSize24);
	LittleFont = TTF_OpenFont("Fonts/VpPixel.ttf", 20);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void CloseSDL(
    void
) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	CurrentClip = NULL;
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void InitFrames(
    const unsigned char TotalFrames,
    SDL_Rect SpriteClips[],
    unsigned char CurrentBlockSize
) {
	unsigned short counter = 0;
	for(unsigned char i = 0; i < TotalFrames; ++i)
    {
		SpriteClips[i].x = counter;
		SpriteClips[i].y = 0;
		SpriteClips[i].w = CurrentBlockSize;
		SpriteClips[i].h = CurrentBlockSize;
		counter += CurrentBlockSize;
	}
}
