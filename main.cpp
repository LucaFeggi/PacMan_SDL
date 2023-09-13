#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



#include "headers/Globals.hpp"
#include "headers/Timer.hpp"



#include "headers/Texture.hpp"
#include "headers/Position.hpp"
#include "headers/Entity.hpp"
#include "headers/Pac.hpp"
#include "headers/Ghost.hpp"
#include "headers/Blinky.hpp"
#include "headers/Inky.hpp"
#include "headers/Pinky.hpp"
#include "headers/Clyde.hpp"
#include "headers/Fruit.hpp"
#include "headers/Board.hpp"
#include "headers/Sound.hpp"

#include "headers/Game.hpp"





//Use arrow keys or WASD to move

int main(int argc, char* args[]){

	InitializeSDL();
    
    Game mGame;
    mGame.Start();

    //  game loop
	bool quit = false;
	while(!quit){

		uint64_t IterationStart = SDL_GetPerformanceCounter();
        
        quit = mGame.keyboardProcess();

		mGame.Process();
		
		uint64_t IterationEnd = SDL_GetPerformanceCounter();


		float elapsedMS = (IterationEnd - IterationStart) / ((float)SDL_GetPerformanceFrequency() * 1000.0f);
		SDL_Delay(floor(11.111f - elapsedMS));

	}
    
    // game loop ended
	CloseSDL();
	
	return 0;
	
}
