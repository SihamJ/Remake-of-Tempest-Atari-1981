#include "Audio.hpp"

Audio::Audio(){}

Audio::~Audio(){}

void Audio::init(){

    SDL_memset(&(this->spectre), 0, sizeof(this->spectre));

    this->spectre.freq = 96000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    this->spectre.format = AUDIO_F32SYS;
    this->spectre.channels = 1; // mono
    this->spectre.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
    this->spectre.callback = [](void* param, Uint8* stream, int len)

    {
        // Envoyez les données dans notre buffer...
        int samples = len / sizeof(float); // 4096

        for (auto i = 0; i < samples; i++)
        {
            reinterpret_cast<float*>(stream)[i] = 0.5 * SDL_sinf(2 * M_PI * i / 1000);
        }
    };

    this->device = SDL_OpenAudioDevice(nullptr, 0, &(this->spectre), &(this->spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    this->time.add_clock();
}

void Audio::shoot(Uint32 time){

    this->time.reset_clock(0);

    SDL_PauseAudioDevice(device, SDL_FALSE);
    while(this->time.get_clock(0) < 100);
    SDL_PauseAudioDevice(device, SDL_TRUE);
}