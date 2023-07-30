#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{
    
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        
    public:
        Window(const char* title, int width, int height);
};