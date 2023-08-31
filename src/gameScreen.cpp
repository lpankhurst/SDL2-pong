#include "GameScreen.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

void GameScreen::drawBackground(SDL_Renderer* _renderer)
{
    SDL_SetRenderDrawColor(_renderer, 30, 30, 30, 255);
}

void GameScreen::drawHalfwayLine(SDL_Renderer* _renderer)
{   
    for (int y = 12; y < 400; y=y+50)
    {   
        SDL_Rect dot = { static_cast<int>(300), static_cast<int>(y), 8, 25 };
        SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 40);
        SDL_RenderFillRect(_renderer, &dot);
    }
}

void GameScreen::drawScores(SDL_Renderer* _renderer, TTF_Font* font, int player1Score, int player2Score)
{   
    SDL_Color White = {255, 255, 255};
    std::string scoreString = std::to_string(player1Score) + "  " + std::to_string(player2Score);
    const char* scoreDisplay = scoreString.c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, scoreDisplay, White); 
    // Better to use Textures to utilise the gpu
    SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage); 
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 245;  //controls the rect's x coordinate 
    Message_rect.y = 10; // controls the rect's y coordinte
    Message_rect.w = 120; // controls the width of the rect
    Message_rect.h = 35; // controls the height of the rect

    SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}



