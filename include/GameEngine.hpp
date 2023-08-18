#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "AudioManager.hpp"
#include "GameScreen.hpp"


class GameEngine{

    private:
        Window window;
        Paddle player1_paddle;
        Paddle player2_paddle;
        Ball ball;
        AudioManager audio;
        int player1Score;
        int player2Score;
    public:
        GameEngine(const int WIN_WIDTH, const int WIN_HEIGHT);
        void initSDL();
        void handleInputs();
        bool isRunning();
        void closeAll();
        void checkAllCollisions();
        void RenderNewFrame();
        void player1Scored();
        void player2Scored();
        


};