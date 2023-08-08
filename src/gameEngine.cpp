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
	audio = AudioManager();
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


void GameEngine::handleInputs()
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{	
		// Prevent double pressing bugginess
		if (event.type == SDL_KEYDOWN ) // Temporary solution -- Not perfect
		{
			player1_paddle.pollEvents();
			player2_paddle.pollEvents();
		}
		window.pollEvents(event);
	}
}

bool GameEngine::isRunning()
{
    if ( window.isOpen )
        return true;

    return false;
}

void GameEngine::closeAll()
{
    window.destroyWindowAndRenderer();
	SDL_Quit();
	IMG_Quit();
	// Mix_Quit();
	// TTF_CloseFont(font);
	// TTF_Quit();
	
}

void GameEngine::updateObjectsPositions()
{	
	
	if( ball.checkPaddleCollision(player1_paddle.getPos(), player2_paddle.getPos()) )
	{
		audio.loadSound("res/audio/sfx_sounds_impact14.wav");
		audio.playSound();
	}
    if ( ball.checkCollision() )
	{
		audio.loadSound("res/audio/sfx_sounds_Blip2.wav");
		audio.playSound();
	}
	// audio.freeSound();
}

void GameEngine::RenderNewFrame()
{
    window.clearRenderer(); // clear prev render
    player1_paddle.draw(window.getRenderer()); // draw paddle1
    player2_paddle.draw(window.getRenderer()); // draw paddle2 
    ball.draw(window.getRenderer()); // draw ball
    window.draw(); // draw background 
    window.presentRenderer(); // present the renderer to the screen 
}