#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Headers/Globals.hpp"
#include "Headers/Texture.hpp"
#include "Headers/Timer.hpp"
#include "Headers/Position.hpp"
#include "Headers/Entity.hpp"
#include "Headers/Pac.hpp"
#include "Headers/Ghost.hpp"
#include "Headers/Blinky.hpp"
#include "Headers/Inky.hpp"
#include "Headers/Pinky.hpp"
#include "Headers/Clyde.hpp"
#include "Headers/Fruit.hpp"
#include "Headers/Board.hpp"
#include "Headers/Sound.hpp"
#include "Headers/Game.hpp"

//Use arrow keys or WASD to move

int main(int argc, char* args[]){

	InitializeSDL();

	Game mGame;
    mGame.gameLoop();
	
	CloseSDL();
	
	return 0;
	
}
