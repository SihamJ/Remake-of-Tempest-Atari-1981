#include "Audio.hpp"

extern int SOUND;
extern int MENUSOUND;
extern int GAMEOVERSOUND;
extern int SHOOTSOUND;

Audio::Audio(){
    
}

Audio::~Audio(){}

void Audio::shoot(Uint32 time){

    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;

    SDL_memset(&(spectre), 0, sizeof(spectre));
    Timer timer = Timer();

    spectre.freq = 48000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spectre.format = AUDIO_F32SYS;
    spectre.channels = 2; // mono
    spectre.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
    spectre.callback = [](void* param, Uint8* stream, int len)

    {
        // Envoyez les données dans notre buffer...
        int samples = len / sizeof(float); // 4096

        for (auto i = 0; i < samples; i++)
        {
            reinterpret_cast<float*>(stream)[i] = 0.5 * SDL_sinf(2 * M_PI * i / 40000);
        }
    };

    
    timer.add_clock();
    while(SOUND){
        while(!SHOOTSOUND);
        device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(7,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
        timer.reset_clock(0);
        SDL_PauseAudioDevice(device, SDL_FALSE);
        SDL_PauseAudioDevice(device, SDL_TRUE);
        SDL_CloseAudioDevice(device);
        SHOOTSOUND=0;
    }
}

void Audio::menu_sound(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    SDL_memset(&(spectre), 0, sizeof(spectre));
    spectre.freq = 4100; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spectre.format = AUDIO_F32SYS;
    spectre.channels = 2; // mono
    spectre.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
    spectre.callback = [](void* param, Uint8* stream, int len)

    {
        // Envoyez les données dans notre buffer...
        int samples = len / sizeof(float); // 4096

        for (auto i = 0; i < samples; i++)
        {   
            reinterpret_cast<float*>(stream)[i] = 1 * SDL_sinf(2 * M_PI * i / 100);
        }
    };

    

    while(SOUND){
            while(!MENUSOUND);
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(8,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
    }

}

void Audio::game_over_sound(){

        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
    
        SDL_memset(&(spectre), 0, sizeof(spectre));
        spectre.freq = 4100; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
        spectre.format = AUDIO_F32SYS;
        spectre.channels = 2; // mono
        spectre.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
        spectre.callback = [](void* param, Uint8* stream, int len)

        {
            // Envoyez les données dans notre buffer...
            int samples = len / sizeof(float); // 4096

            for (auto i = 0; i < samples; i++)
            {   
                reinterpret_cast<float*>(stream)[i] = 0.5 * SDL_sinf(2 * M_PI * i / 100);
            }
        };

        

        while(SOUND){
            while(!GAMEOVERSOUND);
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(3,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
        }
}
