#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Window.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class GameEngine{

    private:
        Window window;
        Paddle player1_paddle;
        Paddle player2_paddle;
        Ball ball;
    public:
        GameEngine(const int WIN_WIDTH, const int WIN_HEIGHT);
        void initSDL();
        void pollEvents(Window &window, Paddle &paddle1, Paddle &paddle2);
        void gameLoop();
        bool isRunning();
        void closeAll();

};