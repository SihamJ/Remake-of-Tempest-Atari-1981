#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__

#include "Timer.hpp"
#include <SDL.h>

class Audio {
    public:
        Audio();
        ~Audio();

        void init();
        void shoot(Uint32 time);

    private:
        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
        Timer time;
};

#endif