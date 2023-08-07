#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{
    
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        
    public:
        Window();
        Window(const char* title, int width, int height);
        void pollEvents(SDL_Event &event);
        void destroy();
        void draw();
        void clearRenderer();
        void presentRenderer();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
        bool isOpen;



};