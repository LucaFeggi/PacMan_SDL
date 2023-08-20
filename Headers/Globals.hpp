#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

const unsigned char BoardWidth = 28;
const unsigned char BoardHeight = 36;
const unsigned char BlockSize32 = 32;
const unsigned char BlockSize24 = 24;
const unsigned short WindowWidth = BoardWidth * BlockSize24;
const unsigned short WindowHeight = BoardHeight * BlockSize24;

const std::string CharBoard =
	"                            "
	"                            "
	"                            "
	"############################"
	"#............##............#"
	"#.####.#####.##.#####.####.#"
	"#o####.#####.##.#####.####o#"
	"#.####.#####.##.#####.####.#"
	"#..........................#"
	"#.####.##.########.##.####.#"
	"#.####.##.########.##.####.#"
	"#......##....##....##......#"
	"######.##### ## #####.######"
	"     #.##### ## #####.#     "
	"     #.##    1     ##.#     "
	"     #.## ###==### ##.#     "
	"######.## #      # ##.######"
	"      .   #2 3 4 #   .      "
	"######.## #      # ##.######"
	"     #.## ######## ##.#     "
	"     #.##          ##.#     "
	"     #.## ######## ##.#     "
	"######.## ######## ##.######"
	"#............##............#"
	"#.####.#####.##.#####.####.#"
	"#.####.#####.##.#####.####.#"
	"#o..##.......0 .......##..o#"
	"###.##.##.########.##.##.###"
	"###.##.##.########.##.##.###"
	"#......##....##....##......#"
	"#.##########.##.##########.#"
	"#.##########.##.##########.#"
	"#..........................#"
	"############################"
	"                            "
	"                            ";

const unsigned char LivingPacFrames = 3;
const unsigned char DeathPacFrames = 10;
const unsigned char GhostBodyFrames = 6;
const unsigned char GhostEyeFrames = 5;
const unsigned char FruitFrames = 8;

const unsigned short ScoreTable[FruitFrames] = {100, 300, 500, 700, 1000, 2000, 3000, 5000};

const SDL_Color Black = {0x00, 0x00, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color Red = {0xff, 0x00, 0x00};
const SDL_Color Cyan = {0x00, 192, 0xff};
const SDL_Color Pink = {0xff, 192, 203};
const SDL_Color Orange = {0xff, 128, 0x00};

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Rect* CurrentClip;
extern TTF_Font* Font;
extern TTF_Font* LittleFont;

enum BlockType{
	Wall,
	Door,
	Pellet,
	Energizer,
	Nothing,
};

enum Direction{
	Right,
	Up,
	Left,
	Down,
	Nowhere,
};

enum EntityType{
	ePacMan,
	eBlinky,
	eInky,
	ePinky,
	eClyde,
	Noone,
};

void InitializeSDL(
	void
);

void CloseSDL(
	void
);

void InitFrames(
	const unsigned char TotalFrames,
	SDL_Rect SpriteClips[],
	unsigned char CurrentBlockSize = BlockSize32
);
