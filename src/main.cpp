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
	GameEngine gameEngine = GameEngine(WIN_WIDTH, WIN_HEIGHT);
	gameEngine.initSDL();

	while ( gameEngine.isRunning() )
	{
		gameEngine.handleInputs();
		gameEngine.checkAllCollisions();
		gameEngine.RenderNewFrame();
		SDL_Delay(10); // Delay between frames 
	}

	gameEngine.closeAll();

	return 0;
}