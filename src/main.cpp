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

	while ( gameEngine.isRunning() )
	{
		gameEngine.gameLoop();
	}

	gameEngine.closeAll();

	return 0;
}