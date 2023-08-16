#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Window{
    
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        TTF_Font* font;
        
    public:
        bool isOpen;
        Window();
        Window(const char* title, int width, int height);
        void pollEvents(SDL_Event &event);
        void destroyWindowAndRenderer();
        void drawBackground();
        void drawHalfwayLine();
        void clearRenderer();
        void presentRenderer();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
        void drawScores(int player1Score, int player2Score);
        void initFont();



};