#include "GameEngine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

//  								{ x, y, width, height}
SDL_Rect GameEngine::arrowContainer = {210, 140, 20, 20};
SDL_Rect GameEngine::messageContainer = {240, -1, 130, 20};
SDL_Color White = {255, 255, 255};

GameEngine::GameEngine()
{
	WIN_WIDTH = 600;
	WIN_HEIGHT = 400;
	window = Window("Pong", WIN_WIDTH, WIN_HEIGHT);
	gameState = 0; // Starting in the start-menu gameState
	audioManager = AudioManager();

	// Setting up the start screen

	const char *filePath = "res/images/arrow.png";
	SDL_Surface *arrowSurface = IMG_Load(filePath);
	if (arrowSurface == NULL)
		std::cout << "Error loading arrow.png" << IMG_GetError() << std::endl;

	arrowTexture = SDL_CreateTextureFromSurface(window.getRenderer(), arrowSurface);
}

// Initialises the objects for the gameplay of the game
void GameEngine::setupGame()
{
	player1_paddle = Paddle(0, 0, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	player2_paddle = Paddle(WIN_WIDTH - 10, 0, SDL_SCANCODE_W, SDL_SCANCODE_S);
	ball = Ball((WIN_WIDTH / 2) - 10, (WIN_HEIGHT / 2) + 10);
	player1Score = player2Score = 0;
}

void GameEngine::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Error Initialising SDL: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "Error Initialising SDL_image: " << SDL_GetError() << std::endl;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cout << "Error Initialising SDL_mixer: " << SDL_GetError() << std::endl;

	if (TTF_Init() < 0)
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

	SDL_Event event;

	if ( SDL_PollEvent(&event) )
		window.pollEvents(event);
}

bool GameEngine::isRunning()
{
	if (window.isOpen)
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

	if (ball.checkPaddleCollision(player1_paddle.getPos(), player2_paddle.getPos(), player1_paddle.getSpeed(), player2_paddle.getSpeed()))
	{
		audioManager.loadSound("res/audio/sfx_sounds_impact14.wav");
		audioManager.playSound();
	}
	else if (ball.checkFloorOrCeilingCollision())
	{
		audioManager.loadSound("res/audio/sfx_sounds_Blip2.wav");
		audioManager.playSound();
	}

	int didPlayerScore = ball.checkIfPlayerScored();
	if (didPlayerScore == 1)
		player1Scored();
	else if (didPlayerScore == 2)
		player2Scored();

	// audio.freeSound();
}

// Draws all the objects to the screen that are involved during the gameplay state
void GameEngine::RenderNewGameFrame()
{
	SDL_Renderer *_renderer = window.getRenderer();
	player1_paddle.draw(_renderer); // draw paddle1
	player2_paddle.draw(_renderer); // draw paddle2
	window.drawHalfwayLine();
	ball.draw(_renderer); // draw ball
	window.drawBackground();
	window.drawScores(font, player1Score, player2Score);
}

// Renders Everything on the start menu
void GameEngine::RenderNewStartFrame()
{
	window.drawBackground();
	drawText("1 Player", 140);
	drawText("2 Player", 190);
	drawText("Quit Game", 240);
	drawArrow();
}

void GameEngine::handleStartInputs()
{
	SDL_Event event;

	if ( SDL_PollEvent(&event) )
	{	
		// See if it is a key-press event
		if ( event.type == SDL_KEYDOWN )
		{	
			// If they are going down
			if (event.key.keysym.sym == SDLK_DOWN)
			{	
				// If we can move down, move down + play sound
				if ( arrowContainer.y < 240 )
				{
					arrowContainer.y += 50;
					audioManager.loadSound("res/audio/sfx_menu_move2.wav");
					audioManager.playSound();
				} 
				// otherwise dont + play different sound
				else {
					audioManager.loadSound("res/audio/sfx_sounds_impact6.wav");
					audioManager.playSound();
				}
			}

			// Same thing for up
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if ( arrowContainer.y > 140 )
				{
					arrowContainer.y -= 50;	
					audioManager.loadSound("res/audio/sfx_menu_move2.wav");
					audioManager.playSound();
				} else {
					audioManager.loadSound("res/audio/sfx_sounds_impact6.wav");
					audioManager.playSound();
				}
			}

			// Start the game and play a sound
			else if (event.key.keysym.sym == SDLK_RETURN)
			{	
				audioManager.loadSound("res/audio/sfx_menu_select1.wav");
				audioManager.playSound();
				setupGame();
				gameState = 1;	
			}

			// Polling to see if closed the window here since best to poll events in one place
			// Otherwise that event might not be polled by the intended place
			window.pollEvents(event);
			
		}
	}
}

// Calls Window methods to present the render to the screen, and clear it for the next frame
void GameEngine::presentRenderer()
{
	window.presentRenderer(); // present the renderer to the screen
	window.clearRenderer();	  // clear prev render
}

void GameEngine::player1Scored()
{
	player1Score++;
	if (player1Score > 7)
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
	if (font == NULL)
		std::cout << "Error Loading Font: " << TTF_GetError() << std::endl;
}

// Draws text to the renderer in White and using the currently loaded font
void GameEngine::drawText(const char *text, int y)
{
	SDL_Renderer *_renderer = window.getRenderer();
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text, White);
	SDL_Texture *Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

	messageContainer.y = y; // controls the rect's y coordinate
	SDL_RenderCopy(_renderer, Message, NULL, &messageContainer);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void GameEngine::drawArrow()
{
	SDL_RenderCopy(window.getRenderer(), arrowTexture, NULL, &arrowContainer);
}