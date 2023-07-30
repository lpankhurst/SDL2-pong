#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Window.hpp"


int WIN_WIDTH = 600;
int WIN_HEIGHT = 400;

int main( int argc, char* argv[] )
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if(!IMG_Init( IMG_INIT_PNG ))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	Window window("My First Window", WIN_WIDTH, WIN_HEIGHT);

	bool gameRunning = true;
	SDL_Event event;

	while ( gameRunning )
	{
		while ( SDL_PollEvent(&event) )
		{
			if ( event.type == SDL_QUIT )
				gameRunning = false;
		}
	}


	return 0;
}
