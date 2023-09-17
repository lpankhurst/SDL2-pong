#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameEngine.hpp"

int main( int argc, char* argv[] )
{
	GameEngine gameEngine = GameEngine();
	gameEngine.initSDL();


	// Gameplay loop
	while ( gameEngine.isRunning() )
	{

		switch ( gameEngine.gameState )
		{
			case 0: // Start-menu state

				// get inputs
				gameEngine.handleStartInputs();
				// update objects
				// Render frame
				gameEngine.RenderNewStartFrame();

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

		if ( SDL_GetError() == NULL )
			std::cout <<  "Error 5" <<SDL_GetError() << std::endl;
	
	}

	gameEngine.closeAll();

	return 0;
}