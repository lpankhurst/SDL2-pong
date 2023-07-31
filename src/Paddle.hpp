#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Paddle{

    private:
        int x_pos;
        int y_pos;
        SDL_Rect paddle;
        SDL_KeyCode up_key;
        SDL_KeyCode down_key;
        

    public:
        Paddle(int x_pos, int y_pos, SDL_KeyCode up_key, SDL_KeyCode down_key);
        void pollEvents(SDL_Event &event);
        void draw(SDL_Renderer* renderer);
        int getPos();

};