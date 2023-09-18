#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "AudioManager.hpp"


class GameEngine{

    private:
        int WIN_WIDTH;
        int WIN_HEIGHT;
        // I dont like that these are all here, will maybe move them 
        SDL_Texture* arrowTexture;
        static SDL_Rect arrowContainer;
        static SDL_Rect messageContainer;
        Window window;
        Paddle player1_paddle;
        Paddle player2_paddle;
        Ball ball;
        AudioManager audioManager;
        int player1Score;
        int player2Score;
        TTF_Font* font;
    public:
        GameEngine();
        void initSDL();
        void handleGameInputs();
        void handleStartInputs();
        void handleEndInputs();
        void handleGenericInputs();
        void RenderNewGameFrame();
        void RenderNewStartFrame();
        void RenderNewEndFrame();
        bool isRunning();
        void closeAll();
        void checkAllCollisions();
        void player1Scored();
        void player2Scored();
        void initFont();
        void presentRenderer();
        void drawText(const char* text, int y);
        void drawArrow();
        void setupGame();
        int gameState;
        
};