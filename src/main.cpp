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

		switch ( gameEngine.gameState )
		{
			case 0: // Start-menu state

				// get inputs
				// gameEngine.handleStartInputs();
				// update objects
				// Render frame
				gameEngine.RenderNewStartFrame();


				// gameEngine.gameState = 1;
				break;

			case 1: // Gameplay state

				gameEngine.handleGameInputs();
				gameEngine.checkAllCollisions();
				gameEngine.RenderNewGameFrame();

				break;

			case 2: // Game over state

				// TODO
				break;

		}
		
		gameEngine.handleGenericInputs();

		// do delta time 
		// Delay
		SDL_Delay(5);
		// Present Renderer & clear for next
		gameEngine.presentRenderer();
	
	}

	gameEngine.closeAll();

	return 0;
}