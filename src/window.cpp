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

void Window::drawBackground()
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
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

void Window::drawHalfwayLine()
{   
    for (int y = 12; y < 400; y=y+50)
    {
        SDL_Rect dot = { static_cast<int>(300), static_cast<int>(y), 8, 25 };
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 40);
        SDL_RenderFillRect(renderer, &dot);
    }
}