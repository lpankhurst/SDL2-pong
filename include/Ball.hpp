#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ball{

    private:
        float x_velocity;
        float y_velocity;
        SDL_Rect ball;

    public:
        Ball();
        Ball(int start_x, int start_y);
        void draw(SDL_Renderer* renderer);
        void checkCollision();
        void checkPaddleCollision(int paddle1_y, int paddle2_y);


};
