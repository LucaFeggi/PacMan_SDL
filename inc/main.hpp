#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define LivingPacFrames 3
#define DeathPacFrames  10
#define GhostBodyFrames 6
#define GhostEyeFrames  5
#define FruitFrames     8

#define BoardWidth   28
#define BoardHeight  36
#define BlockSize32  32
#define BlockSize24  24
#define WindowWidth  (BoardWidth * BlockSize24)
#define WindowHeight (BoardHeight * BlockSize24)

#define Black  ((SDL_Color){0x00, 0x00, 0x00})
#define White  ((SDL_Color){0xff, 0xff, 0xff})
#define Yellow ((SDL_Color){0xff, 0xff, 0x00})
#define Red    ((SDL_Color){0xff, 0x00, 0x00})
#define Cyan   ((SDL_Color){0x00, 192, 0xff})
#define Pink   ((SDL_Color){0xff, 192, 203})
#define Orange ((SDL_Color){0xff, 128, 0x00})

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Rect* CurrentClip;
extern TTF_Font* Font;
extern TTF_Font* LittleFont;
extern std::string build_path;

void InitializeSDL();
void CloseSDL();
void InitFrames(const unsigned char TotalFrames, SDL_Rect SpriteClips[]);
