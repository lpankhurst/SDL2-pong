#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"


const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 400;

void pollEvents(Window &window, Paddle &paddle1, Paddle &paddle2)
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{	
		// Prevent double pressing bugginess
		if (event.type == SDL_KEYDOWN ) // Temporary solution -- Not perfect
		{
			paddle1.pollEvents();
			paddle2.pollEvents();
		}
		window.pollEvents(event);
	}
}

void initSDL()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if(!IMG_Init( IMG_INIT_PNG ))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	if(SDL_Init(SDL_INIT_AUDIO))
		std::cout << "Error Initialising SDL_mixer: " << SDL_GetError() << std::endl;
}

int main( int argc, char* argv[] )
{
	
	initSDL();

	// Instantiating the window
	Window window("Pong", WIN_WIDTH, WIN_HEIGHT);
	// Instantiating the paddles
	Paddle player1_paddle(0, 0, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	Paddle player2_paddle(WIN_WIDTH - 10, 0, SDL_SCANCODE_W, SDL_SCANCODE_S);
	// Instantiate the ball
	Ball ball( (WIN_WIDTH/2) - 10 , (WIN_HEIGHT/2) + 10 );


	while ( window.isOpen )
	{
		// Clear the last Render
		window.clearRenderer();
		// Increase the time between frames 
		SDL_Delay(10);
		// Check user input(s)
		pollEvents(window, player1_paddle, player2_paddle);
		// Draw to and present the new renderer
		player1_paddle.draw(window.getRenderer());
		player2_paddle.draw(window.getRenderer());
		ball.checkPaddleCollision(player1_paddle.getPos(),player2_paddle.getPos());
		ball.draw(window.getRenderer());
    	ball.checkCollision();
		window.draw();
		window.presentRenderer();

	}

	// Destroy the window after closing 
	window.destroy();

	return 0;
}