#include "AudioManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

AudioManager::AudioManager(){}

void AudioManager::loadSound(const char* filePath)
{
    sound = Mix_LoadWAV(filePath);
}

void AudioManager::playSound()
{
    Mix_PlayChannel(-1, sound, 1);
}

void AudioManager::freeSound()
{
    Mix_FreeChunk(sound);
}