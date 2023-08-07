#include "Ball.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Ball::Ball(int start_x, int start_y)
{   
    // Setting the initial position of the ball
    ball.y = start_y;
    ball.x = start_x;
    // Size of the ball
    ball.w = ball.h = 10;
    // Start velocitiy of the ball
    x_velocity = y_velocity = 1;
}

Ball::Ball(){}

void Ball::draw(SDL_Renderer* renderer)
{
    // Move according to the current velocities
    ball.x += x_velocity;
    ball.y += y_velocity;
    
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &ball);
}

void Ball::checkCollision()
{
    if ( ball.x > 600 - ball.w || ball.x < 0 )
        x_velocity *= -1;
    else if ( ball.y > 400 - ball.h || ball.y < 0)
        y_velocity *= -1;
}

void Ball::checkPaddleCollision(int paddle1_y, int paddle2_y)
{
    if ( ball.x == 10 || ball.x == 590 - ball.w )
        x_velocity *= -1;

}