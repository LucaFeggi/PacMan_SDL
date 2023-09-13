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
	Timer GameTimer;
	
    bool quit = false;
	unsigned short StartTicks = 4500;

    GameTimer.Start();
	mGame.mSound.PlayIntro();

	while(!quit){

		double IterationStart = SDL_GetPerformanceCounter();

        quit = mGame.keyboardProcess();

		SDL_RenderClear(renderer);

		if(mGame.Process(GameTimer, StartTicks)){
			mGame.Draw();
			SDL_RenderPresent(renderer);
		}
		
		double IterationEnd = SDL_GetPerformanceCounter();
		double ElapsedSeconds = (IterationEnd - IterationStart) / (double)SDL_GetPerformanceFrequency();
		double Delay = 16.666f - (ElapsedSeconds * 1000.0f);
		if (Delay > 0)
			SDL_Delay(std::max(0, (int) Delay));
		
	}
	
	CloseSDL();
	
	return 0;
	
}
