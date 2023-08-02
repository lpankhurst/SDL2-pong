#include "Paddle.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Paddle::Paddle(int x, int y, SDL_Scancode up, SDL_Scancode down)
{
    // Paddle's dimensions
    paddle.w = 20;
    paddle.h = 100;
    // Paddles position
    paddle.x = x_pos = x;
    paddle.y = y_pos = y;
    // Setting the Up and Down key-bindings
    up_key = up;
    down_key = down;

}

void Paddle::pollEvents()
{
    // 
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if ( state[up_key] )
        y_pos -= 10;
    else if ( state[down_key] )
        y_pos += 10;

}

    
void Paddle::draw(SDL_Renderer* renderer)
{
    // Update the position of the paddle
    paddle.y = y_pos;
    
    // Set the color of the paddle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &paddle);

}

int Paddle::getPos()
{
    return y_pos;
}