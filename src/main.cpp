#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameEngine.hpp"


const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 400;

int main( int argc, char* argv[] )
{	
	// Start-menu loop


	GameEngine gameEngine = GameEngine(WIN_WIDTH, WIN_HEIGHT);
	gameEngine.initSDL();

	// Gameplay loop
	while ( gameEngine.isRunning() )
	{
		gameEngine.handleInputs();
		gameEngine.checkAllCollisions();
		gameEngine.RenderNewFrame();
		SDL_Delay(5); // Delay between frames 
	}
	
	// Not sure if fixed or hard to replicate error, but "Bus Error 10" used to happen here 
	gameEngine.closeAll();

	return 0;
}