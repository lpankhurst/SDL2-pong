#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include <Window.hpp>

// This class draws the elements that should appear on the screen while playing the game
// I.e not in a menu 
class GameScreen : public Window{
    private:
    public:
        GameScreen();
        void drawBackground(SDL_Renderer* renderer);
        void drawHalfwayLine(SDL_Renderer* renderer);
        void drawScores(SDL_Renderer* renderer, TTF_Font* font, int player1Score, int player2Score);

};