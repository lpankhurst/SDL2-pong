#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect{ 
    private:
        Mix_Chunk* sound;
    public:
        SoundEffect(const std::string filePath, bool asChunk);

};