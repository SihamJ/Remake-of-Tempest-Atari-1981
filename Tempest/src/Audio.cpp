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

    spectre.freq = 192000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spectre.format = AUDIO_F32SYS;
    spectre.channels = 1; // mono
    spectre.samples = 32768; // Oublier pas que ce sa doit être en puissance de deux 2^n
    spectre.callback = [](void* param, Uint8* stream, int len)

    {
        // Envoyez les données dans notre buffer...
        int samples = len / sizeof(float); // 4096

        for (auto i = 0; i < samples; i++)
        {
            // reinterpret_cast<float*>(stream)[i] = 0.5 * SDL_sinf(2 * M_PI * i / 40000);
            reinterpret_cast<float*>(stream)[i] = shoot_sound.at(i);
        }
    };

    
    timer.add_clock();
    while(SOUND){
        while(!SHOOTSOUND){ if(!SOUND) break ;}
        if(!SOUND) break;
        device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
        timer.reset_clock(0);
        SDL_PauseAudioDevice(device, SDL_FALSE);
        while(timer.get_clock(0)<20);
        SDL_PauseAudioDevice(device, SDL_TRUE);
        SDL_CloseAudioDevice(device);
        SHOOTSOUND=0;
    }
}

void Audio::play_menu_sound(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    SDL_memset(&(spectre), 0, sizeof(spectre));
    spectre.freq = 4100; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spectre.format = AUDIO_F32SYS;
    spectre.channels = 2; // mono
    spectre.samples = 32768; // Oublier pas que ce sa doit être en puissance de deux 2^n
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
            while(!MENUSOUND) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            while(MENUSOUND);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
    }

}

void Audio::play_game_over_sound(){

        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
    
        SDL_memset(&(spectre), 0, sizeof(spectre));
        spectre.freq = 48000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
        spectre.format = AUDIO_F32SYS;
        spectre.channels = 2; // mono
        spectre.samples = 32768; // Oublier pas que ce sa doit être en puissance de deux 2^n
        spectre.callback = [](void* param, Uint8* stream, int len)

        {
            // Envoyez les données dans notre buffer...
            int samples = len / sizeof(float); // 4096
            bool first = true;
            for (auto i = 0; i < samples; i++)
            {   
                if(first == true && game_over_sound.at(i) == 0){
                    first = false;
                    continue;
                }
                reinterpret_cast<float*>(stream)[i] = game_over_sound.at(i);
            }
        };

        

        while(SOUND){
            while(!GAMEOVERSOUND) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            while(GAMEOVERSOUND);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
        }
}
