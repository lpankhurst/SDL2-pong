#include "GameEngine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>


GameEngine::GameEngine(const int WIN_WIDTH, const int WIN_HEIGHT)
{
    window = Window("Pong", WIN_WIDTH, WIN_HEIGHT); 
	player1_paddle = Paddle(0, 0, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	player2_paddle = Paddle(WIN_WIDTH - 10, 0, SDL_SCANCODE_W, SDL_SCANCODE_S);
	ball = Ball( (WIN_WIDTH/2) - 10 , (WIN_HEIGHT/2) + 10 );
}

void GameEngine::initSDL()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if(!IMG_Init( IMG_INIT_PNG ))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	if(SDL_Init( SDL_INIT_AUDIO ) < 0 )
		std::cout << "Error Initialising SDL_mixer: " << SDL_GetError() << std::endl;
}


void GameEngine::pollEvents(Window &window, Paddle &paddle1, Paddle &paddle2)
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

void GameEngine::gameLoop()
{
    window.clearRenderer(); // clear prev render
    SDL_Delay(10); // add delay between frames
    pollEvents(window, player1_paddle, player2_paddle); // check for user inputs related to each object
    player1_paddle.draw(window.getRenderer()); // draw paddle1
    player2_paddle.draw(window.getRenderer()); // draw paddle2 
    ball.checkPaddleCollision(player1_paddle.getPos(), player2_paddle.getPos()); // check if ball hit paddle
    ball.draw(window.getRenderer()); // draw ball
    ball.checkCollision(); // check ball hit wall 
    window.draw(); // draw background 
    window.presentRenderer(); // present the renderer to the screen 
}

bool GameEngine::isRunning()
{
    if ( window.isOpen )
        return true;

    return false;
}

void GameEngine::closeAll()
{
    window.destroy();
}

