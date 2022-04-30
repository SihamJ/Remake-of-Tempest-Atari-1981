#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__

#include "Timer.hpp"
#include <SDL.h>
#include <iostream>

class Audio {
    public:
        Audio();
        ~Audio();

        void shoot(Uint32 time);
        void menu_sound();
        void game_over_sound();

    private:
        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
};

#endif