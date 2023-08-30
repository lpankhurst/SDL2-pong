#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameEngine.hpp"

// TODO add fullscreen option 
const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 400;

int main( int argc, char* argv[] )
{
	GameEngine gameEngine = GameEngine(WIN_WIDTH, WIN_HEIGHT);
	gameEngine.initSDL();


	// Gameplay loop
	while ( gameEngine.isRunning() )
	{
		// gameEngine.handleInputs();
		// gameEngine.checkAllCollisions();
		// gameEngine.RenderNewFrame();
		// SDL_Delay(5); // Delay between frames
		

		switch ( gameEngine.gameState )
		{
			case 0: // Start-menu state

				// get inputs
				// update objects
				// Render frame
				std::cout << "Start-menu exitted" << std::endl;
				gameEngine.gameState = 1;
				break;

			case 1: // Gameplay state

				gameEngine.handleInputs();
				gameEngine.checkAllCollisions();
				gameEngine.RenderNewFrame();

				break;

			case 2: // Game over state

				break;

		}

		// Delay
		SDL_Delay(5);
		// Present Renderer
		// Clear Renderer ** maybe do before switch statement

		// break;
	
	}

	gameEngine.closeAll();

	return 0;
}