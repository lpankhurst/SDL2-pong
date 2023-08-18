#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include <Window.hpp>

// This class draws the elements that should appear on the screen while playing the game
// I.e not in a menu 
class GameScreen : public Window{
    private:
        Window window;
    public:
        GameScreen(Window win);
        void drawBackground();
        void drawHalfwayLine();
        void drawScores(int player1Score, int player2Score);

};