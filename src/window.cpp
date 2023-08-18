#include "Window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <string>

Window::Window(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
    // Create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if ( window == NULL )
        std::cout << "Error Creating Window: " << SDL_GetError() << std::endl;
    
    // Tell the gameloop the window is open
    isOpen = true;

    // Create the renderer onto the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( renderer == NULL )
        std::cout << "Error Creating Renderer: " << SDL_GetError() << std::endl; 
}

Window::Window(){}

void Window::pollEvents(SDL_Event &event)
{
    bool closedWindow = ( event.type == SDL_QUIT );
    bool pressedEscape = ( event.key.keysym.sym == SDLK_ESCAPE );
    if ( closedWindow || pressedEscape )
    {
        isOpen = false;
    }

}

void Window::destroyWindowAndRenderer()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Window::clearRenderer()
{
    SDL_RenderClear(renderer);
}

void Window::presentRenderer()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}
