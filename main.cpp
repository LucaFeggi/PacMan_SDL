#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



#include "Headers/Globals.hpp"
#include "Headers/Timer.hpp"



#include "Headers/Texture.hpp"
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
    mGame.Start();

    //  game loop
	bool quit = false;
	while(!quit){

		uint64_t IterationStart = SDL_GetPerformanceCounter();
        

        // processing of keyboard input
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT)
				quit = true;
			if(event.key.state == SDL_PRESSED){
				if((event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))		mGame.mover.push_back(Right);
				else if((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)) 	mGame.mover.push_back(Up);	
				else if((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))	mGame.mover.push_back(Left);	
				else if((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s))	mGame.mover.push_back(Down);	
				if(mGame.mover.size() > 2)
					mGame.mover.erase(mGame.mover.begin() + 1);
			}
		}


		mGame.Process();
		
		uint64_t IterationEnd = SDL_GetPerformanceCounter();


		float elapsedMS = (IterationEnd - IterationStart) / ((float)SDL_GetPerformanceFrequency() * 1000.0f);
		SDL_Delay(floor(11.111f - elapsedMS));

	}
    
    // game loop ended
	CloseSDL();
	
	return 0;
	
}
