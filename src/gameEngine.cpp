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

// Handles inputs concerning during the gameplay game state
void GameEngine::handleGameInputs()
{
	// !! Not great but works

	// Get the entire state of the keyboard 
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	// See if any keys are pressed that would move a paddle
	player1_paddle.pollEvents(state); 
	player2_paddle.pollEvents(state);
	
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

// Draws all the objects to the screen that are involved during the gamplay state
void GameEngine::RenderNewGameFrame()
{
	SDL_Renderer* _renderer = window.getRenderer();
    player1_paddle.draw(_renderer); // draw paddle1
    player2_paddle.draw(_renderer); // draw paddle2 
	Window::drawHalfwayLine(_renderer);
    ball.draw(_renderer); // draw ball
	Window::drawBackground(_renderer);
	Window::drawScores(_renderer, font, player1Score, player2Score);

}

// Renders Everything on the start menu
void GameEngine::RenderNewStartFrame()
{
	SDL_Renderer* _renderer = window.getRenderer();

	SDL_SetRenderDrawColor(_renderer, 10, 0, 10, 255); // Draw bg color
	drawText("Hello", 100, 20, 50 ,50);

}

// Calls Window methods to present the render to the screen, and clear it for the next frame
void GameEngine::presentRenderer()
{
    window.presentRenderer(); // present the renderer to the screen 
    window.clearRenderer(); // clear prev render

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

// Draws text to the renderer in White and using the currently loaded font
void GameEngine::drawText(const char* text, int w, int h, int x, int y)
{	
	SDL_Renderer* _renderer = window.getRenderer();
	SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White); 
    // Better to use Textures to utilise the gpu
    SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage); 
    SDL_Rect Message_rect; //create a rect
    Message_rect.w = w; // controls the width of the rect
    Message_rect.h = h; // controls the height of the rect
    Message_rect.x = x;  //controls the rect's x coordinate 
    Message_rect.y = y; // controls the rect's y coordinte
    SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

// Handles inputs relevant to all game state types such as closing of the window
void GameEngine::handleGenericInputs()
{	
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{	
		window.pollEvents(event);
	}
}




