#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__

#include "Timer.hpp"
#include <SDL.h>
#include <iostream>
#include <array>

#include "Utils.hpp"

class Audio {
    public:
        Audio();
        ~Audio();

        void shoot(Uint32 time);
        void play_menu_sound();
        void play_game_over_sound();
        

    private:
        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;

        float a = 1.410000000000000000e+03;
        

};

#endif