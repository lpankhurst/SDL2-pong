#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// This class draws the elements that should appear on the screen while playing the game
// I.e not in a menu 
class GameScreen{
    private:
    public:
        GameScreen(){};
        static void drawBackground(SDL_Renderer* renderer);
        static void drawHalfwayLine(SDL_Renderer* renderer);
        static void drawScores(SDL_Renderer* renderer, TTF_Font* font, int player1Score, int player2Score);

};