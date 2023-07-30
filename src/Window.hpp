#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{
    
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        
    public:
        bool isOpen;

        Window(const char* title, int width, int height);
        void pollEvents(SDL_Event &event);
        void destroy();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();



};