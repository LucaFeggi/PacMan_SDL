#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect* CurrentClip = NULL;
TTF_Font* Font = NULL;
TTF_Font* LittleFont = NULL;

enum BlockType{
	Wall, Door, Pellet, Energizer, Nothing
};

enum Direction{
	Right, Up, Left, Down, Nowhere
};

enum EntityType{
	ePacMan, eBlinky, eInky, ePinky, eClyde, Noone
};

void InitializeSDL(){
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

void CloseSDL(){
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

void InitFrames(const unsigned char TotalFrames, SDL_Rect SpriteClips[], unsigned char CurrentBlockSize = BlockSize32){
	unsigned short counter = 0;
	for(unsigned char i = 0; i < TotalFrames; i++){
		SpriteClips[i].x = counter;
		SpriteClips[i].y = 0;
		SpriteClips[i].w = CurrentBlockSize;
		SpriteClips[i].h = CurrentBlockSize;
		counter += CurrentBlockSize;
	}
}
