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

        void shoot();
        void menu();
        void pause();
        void gameover();
        void player_touche();
        void enemy_shoot();
        void inc_score();
        void superzapper();
        void flipper_attack();
        void next_level();

    private:
        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;

        float a = 1.410000000000000000e+03;
        

};

#endif