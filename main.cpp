#include "Headers/Game.hpp"

//Use arrow keys or WASD to move

int main(int argc, char* args[]){
	InitializeSDL();

	Game mGame;
    mGame.gameLoop();

	CloseSDL();
	
	return 0;
	
}
