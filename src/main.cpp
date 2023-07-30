#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"


int WIN_WIDTH = 600;
int WIN_HEIGHT = 400;

void pollEvents(Window &window, Paddle &paddle)
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{
		paddle.pollEvents(event);
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

	// Instantiating the paddle
	Paddle paddle(0, 0);

	while ( window.isOpen )
	{
		pollEvents(window, paddle);
		paddle.draw(window.getRenderer());
	}

	// Destroy the window after closing 
	window.destroy();

	return 0;
}