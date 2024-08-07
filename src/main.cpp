#include "main.hpp"

#include "Blinky.hpp"
#include "Board.hpp"
#include "Clyde.hpp"
#include "Entity.hpp"
#include "Fruit.hpp"
#include "Game.hpp"
#include "Ghost.hpp"
#include "Inky.hpp"
#include "Pac.hpp"
#include "Pinky.hpp"
#include "Position.hpp"
#include "Sound.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

#include <iostream>
#include <filesystem>

// Use arrow keys or WASD to move
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect* CurrentClip = NULL;
TTF_Font* Font = NULL;
TTF_Font* LittleFont = NULL;
std::string build_path = "";

int main(int argc, char* args[]) {
    char* last = strrchr(args[0], '/');
    if (last != NULL) {
        *++last = '\0';
        build_path = args[0];
    }
    InitializeSDL();

    Game mGame;
    Timer GameTimer;
    SDL_Event event;
    bool quit = false;
    unsigned short StartTicks = 4500;
    std::vector<Position::Direction> mover;
    mover.push_back(Position::Direction::Right);
    GameTimer.Start();
    mGame.mSound.PlayIntro();

    while (!quit) {
        double IterationStart = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.key.state == SDL_PRESSED) {
                if ((event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))
                    mover.push_back(Position::Direction::Right);
                else if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w))
                    mover.push_back(Position::Direction::Up);
                else if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))
                    mover.push_back(Position::Direction::Left);
                else if ((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s))
                    mover.push_back(Position::Direction::Down);
                if (mover.size() > 2)
                    mover.erase(mover.begin() + 1);
            }
        }

        SDL_RenderClear(renderer);

        if (mGame.Process(GameTimer, mover, StartTicks)) {
            mGame.Draw();
            SDL_RenderPresent(renderer);
        }

        double IterationEnd = SDL_GetPerformanceCounter();
        double ElapsedSeconds = (IterationEnd - IterationStart) / (double)SDL_GetPerformanceFrequency();
        double Delay = 16.666f - (ElapsedSeconds * 1000.0f);
        if (Delay > 0)
            SDL_Delay(std::max(0, (int)Delay));
    }

    CloseSDL();

    return 0;
}

void InitializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
    TTF_Init();
    Font = TTF_OpenFont(std::string(build_path + "Fonts/emulogic.ttf").c_str(), BlockSize24);
    LittleFont = TTF_OpenFont(std::string(build_path + "Fonts/VpPixel.ttf").c_str(), 20);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void CloseSDL() {
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

void InitFrames(const unsigned char TotalFrames, SDL_Rect SpriteClips[]) {
    unsigned char CurrentBlockSize = BlockSize32;
    unsigned short counter = 0;
    for (unsigned char i = 0; i < TotalFrames; i++) {
        SpriteClips[i].x = counter;
        SpriteClips[i].y = 0;
        SpriteClips[i].w = CurrentBlockSize;
        SpriteClips[i].h = CurrentBlockSize;
        counter += CurrentBlockSize;
    }
}
