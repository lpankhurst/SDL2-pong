#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"


int WIN_WIDTH = 600;
int WIN_HEIGHT = 400;

void pollEvents(Window &window, Paddle &paddle1, Paddle &paddle2)
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{
		paddle1.pollEvents(event);
		paddle2.pollEvents(event);
		window.pollEvents(event);
	}
}

int main( int argc, char* argv[] )
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if(!IMG_Init( IMG_INIT_PNG ))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	// Instantiating the window
	Window window("Pong", WIN_WIDTH, WIN_HEIGHT);

	// Instantiating the paddles
	Paddle player1_paddle(0, 0, SDLK_UP, SDLK_DOWN);
	Paddle player2_paddle(WIN_WIDTH - 20, 0, SDLK_w, SDLK_s);


	while ( window.isOpen )
	{
		// Clear the last Render
		window.clearRenderer();
		// Check user input(s)
		pollEvents(window, player1_paddle, player2_paddle);
		// Draw to and present the new renderer
		player1_paddle.draw(window.getRenderer());
		player2_paddle.draw(window.getRenderer());
		window.draw();
		window.presentRenderer();

	}

	// Destroy the window after closing 
	window.destroy();

	return 0;
}