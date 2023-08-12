#include "Paddle.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Paddle::Paddle(int x, int y, SDL_Scancode up, SDL_Scancode down)
{
    // Paddle's dimensions
    paddle.w = 10;
    paddle.h = 100;
    // Paddles position
    paddle.x = x;
    paddle.y = y_pos = y;
    // Setting the Up and Down key-bindings
    up_key = up;
    down_key = down;

    speed = 1;



}

Paddle::Paddle(){}

void Paddle::pollEvents(const Uint8 *state)
{
    bool moveUp = ( state[up_key] && !(paddle.y == 0) );
    bool moveDown = ( state[down_key] && !(paddle.y == 400 - paddle.h) );
    // If the correct key is pressed and not trying to move outside the screen
    if ( moveUp )
    {
        speed = -1;
        y_pos += speed;
    }
    else if ( moveDown )
    {
        speed = 1;
        y_pos += speed;
    }

    paddle.y = y_pos;
}


void Paddle::draw(SDL_Renderer* renderer)
{
    // Update the position of the paddle
    
    // Set the color of the paddle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &paddle);

}

int Paddle::getPos()
{
    return y_pos;
}

int Paddle::getSpeed()
{
    return speed;
}