#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Paddle{

    private:
        int x_pos;
        int y_pos;
        SDL_Rect paddle;
        SDL_Scancode up_key;
        SDL_Scancode down_key;
        

    public:
        Paddle(int x_pos, int y_pos, SDL_Scancode up_key, SDL_Scancode down_key);
        void pollEvents();
        void draw(SDL_Renderer* renderer);
        int getPos();

};