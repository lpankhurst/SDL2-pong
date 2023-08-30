#include "GameEngine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


GameEngine::GameEngine(const int WIN_WIDTH, const int WIN_HEIGHT)
{
    window = Window("Pong", WIN_WIDTH, WIN_HEIGHT); 
	player1_paddle = Paddle(0, 0, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	player2_paddle = Paddle(WIN_WIDTH - 10, 0, SDL_SCANCODE_W, SDL_SCANCODE_S);
	ball = Ball( (WIN_WIDTH/2) - 10 , (WIN_HEIGHT/2) + 10 );
	audio = AudioManager();
	player1Score = player2Score = 0;
	gameState = 0; // Starting in the start-menu gameState
	GameScreen gameScreen = GameScreen();
}

void GameEngine::initSDL()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if(!IMG_Init( IMG_INIT_PNG ))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	if(SDL_Init( SDL_INIT_AUDIO ) < 0 )
		std::cout << "Error Initialising SDL_mixer: " << SDL_GetError() << std::endl;

	if(TTF_Init() < 0)
		std::cout << "Error Initialising SDL_ttf: " << TTF_GetError() << std::endl;

	initFont();
	
}

void GameEngine::handleInputs()
{
	SDL_Event event;

	// No longer update the paddles position only when event is triggered
	// Allows user to hold down keys to move paddles
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	player1_paddle.pollEvents(state);
	player2_paddle.pollEvents(state);
	if ( SDL_PollEvent(&event) )
	{	
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
	// IMG_Quit();
	// Mix_Quit();
	// TTF_CloseFont(font);
	// TTF_Quit();
	
}

void GameEngine::checkAllCollisions()
{	
	
	if( ball.checkPaddleCollision(player1_paddle.getPos(), player2_paddle.getPos(), player1_paddle.getSpeed(), player2_paddle.getSpeed()))
	{
		audio.loadSound("res/audio/sfx_sounds_impact14.wav");
		audio.playSound();
	}
    else if ( ball.checkFloorOrCeilingCollision() )
	{
		audio.loadSound("res/audio/sfx_sounds_Blip2.wav");
		audio.playSound();
	}

	int didPlayerScore = ball.checkIfPlayerScored();
	if ( didPlayerScore == 1 )
		player1Scored();
	else if ( didPlayerScore == 2)
		player2Scored();
	

	// audio.freeSound();
}

void GameEngine::RenderNewFrame()
{
	SDL_Renderer* renderer = window.getRenderer();
    window.clearRenderer(); // clear prev render
    player1_paddle.draw(renderer); // draw paddle1
    player2_paddle.draw(renderer); // draw paddle2 
	gameScreen.drawHalfwayLine(renderer);
    ball.draw(renderer); // draw ball
	gameScreen.drawBackground(renderer);
	gameScreen.drawScores(renderer, font, player1Score, player2Score);
    window.presentRenderer(); // present the renderer to the screen 
}

void GameEngine::player1Scored()
{	
	player1Score++;
	if ( player1Score > 7 )
	{
		std::cout << "Player 1 Won" << std::endl;
	}
	std::cout << "Player 1 Has scored" << std::endl;
	ball.resetRound();


}

void GameEngine::player2Scored()
{	

	player2Score++;
	std::cout << "Player 2 Has scored" << std::endl;
	ball.resetRound();
}

void GameEngine::initFont()
{
	// Loading the font 
    font = TTF_OpenFont("res/fonts/volleyball.ttf", 20);
    if ( font == NULL )
        std::cout << "Error Loading Font: " << TTF_GetError() << std::endl; 
}