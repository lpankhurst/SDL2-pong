#include "Window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Window::Window(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
    // Create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if ( window == NULL )
    {
        std::cout << "Error Creating Window: " << SDL_GetError() << std::endl;
    }

    // Tell the gameloop the window is open
    isOpen = true;

    // Create the renderer onto the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


}

void Window::pollEvents(SDL_Event &event)
{
    if ( event.type == SDL_QUIT )
    {
        isOpen = false;
    }
}

void Window::destroy()
{
    SDL_DestroyWindow(window);
}

SDL_Window* Window::getWindow()
{
    return window;
}


SDL_Renderer* Window::getRenderer()
{
    return renderer;
}
