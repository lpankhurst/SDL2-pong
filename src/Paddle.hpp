#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Paddle{

    private:
        int x_pos;
        int y_pos;
        SDL_Rect paddle;
        

    public:
        Paddle(int x_pos, int y_pos);
        void pollEvents(SDL_Event &event);
        void draw(SDL_Renderer* renderer);

};