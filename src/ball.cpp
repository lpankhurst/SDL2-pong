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
    
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &ball);
}

bool Ball::checkCollision()
{
    if ( ball.x > 600 - ball.w || ball.x < 0 )
    {
        x_velocity *= -1;
        return true;
    }
    else if ( ball.y > 400 - ball.h || ball.y < 0)
    {
        y_velocity *= -1;
        return true;
    }

    return false;
}

bool Ball::checkPaddleCollision(int paddle1_y, int paddle2_y)
{
    bool ballPaddle1SameX = ball.x == 10;
    bool ballPaddle2SameX = ball.x == 590 - ball.w;
    bool ballPaddle1SameY = paddle1_y < ball.y && ball.y < paddle1_y + 100;
    bool ballPaddle2SameY = paddle2_y < ball.y && ball.y < paddle2_y + 100;

    if (( ballPaddle1SameX && ballPaddle1SameY ) || ( ballPaddle2SameX && ballPaddle2SameY ))
    {
            x_velocity *= -1;
            return true;
    }
    return false;

}