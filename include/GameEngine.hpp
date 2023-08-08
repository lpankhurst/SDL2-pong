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
        Window window;
        Paddle player1_paddle;
        Paddle player2_paddle;
        Ball ball;
        AudioManager audio;
    public:
        GameEngine(const int WIN_WIDTH, const int WIN_HEIGHT);
        void initSDL();
        void handleInputs();
        bool isRunning();
        void closeAll();
        void checkAllCollisions();
        void RenderNewFrame();
        


};