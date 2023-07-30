#include "Paddle.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Paddle::Paddle(int x, int y)
{
    // Paddle's dimensions
    paddle.w = 20;
    paddle.h = 100;

    // Paddles position
    paddle.x = x;
    paddle.y = y;
}

void Paddle::pollEvents(SDL_Event &event)
{
    if ( event.type == SDL_KEYDOWN )
    {
        switch ( event.key.keysym.sym )
        {
            case SDLK_UP: 
                // Decrease y_pos to move up
                y_pos -= 10;
                break;
            case SDLK_DOWN:
                // Increase y_pos to move down
                y_pos += 10;
                break;

        }
    }
}

    
void Paddle::draw(SDL_Renderer* renderer)
{
    // Update the position of the paddle
    paddle.y = y_pos;

    // Set the color of the paddle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &paddle);

    // Render to the renderer
    SDL_RenderPresent(renderer);

}
