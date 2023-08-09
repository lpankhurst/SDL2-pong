#include "Ball.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Ball::Ball(int start_x, int start_y)
{   
    // Setting the initial position of the ball
    x_pos = start_y;
    y_pos = start_x;
    // Size of the ball
    ball.w = ball.h = 10;
    // Start velocitiy of the ball
    x_velocity = y_velocity = 0.5;

}

Ball::Ball(){}

void Ball::draw(SDL_Renderer* renderer)
{
    // Move according to the current velocities
    x_pos += x_velocity;
    y_pos += y_velocity;
    
    // Setting the position of the ball like this and not setting ball.x allows 
    // Ball to move by decimal amounts, but is only visually moves when x_pos or y_pos 
    // changes by a whole number (ie at least one pixel)
    SDL_Rect ball = { static_cast<int>(x_pos), static_cast<int>(y_pos), 10, 10 };
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &ball);
}

bool Ball::checkFloorOrCeilingCollision()
{
    if ( y_pos > 400 - ball.h || y_pos < 0)
    {
        y_velocity *= -1;
        return true;
    }

    return false;
}

bool Ball::checkPaddleCollision(int paddle1_y, int paddle2_y)
{
    bool ballPaddle1SameX = x_pos == 10;
    bool ballPaddle2SameX = x_pos == 590 - ball.w;
    bool ballPaddle1SameY = paddle1_y < y_pos && y_pos < paddle1_y + 100;
    bool ballPaddle2SameY = paddle2_y < y_pos && y_pos < paddle2_y + 100;

    if (( ballPaddle1SameX && ballPaddle1SameY ) || ( ballPaddle2SameX && ballPaddle2SameY ))
    {
            x_velocity *= -1;
            return true;
    }
    return false;
}

int Ball::checkIfPlayerScored()
{
    bool ballInPlayer1Area = x_pos < 0;
    bool ballInPlayer2Area = x_pos > 600 - ball.w;

    if ( ballInPlayer1Area )
        return 2;
    else if ( ballInPlayer2Area )
        return 1;
    
    return 0;
}

void Ball::resetRound()
{
    x_pos = 290;
    y_pos = 210;

    x_velocity *= -1;

}