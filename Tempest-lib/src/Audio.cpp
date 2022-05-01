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
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV_RW( SDL_RWFromFile("Audio/shoot.wav", "rb"), 1, &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }
        
    while(SOUND){
        while(!SHOOTSOUND){ if(!SOUND) break ;}
        if(!SOUND) break;
        device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), NULL, 0);
        
        int success = SDL_QueueAudio(device, audio_buf, audio_len);
        SDL_PauseAudioDevice(device, SDL_FALSE);
        SDL_Delay(200);
        SDL_PauseAudioDevice(device, SDL_TRUE);
        SDL_CloseAudioDevice(device);
        SHOOTSOUND=0;
    }
    SDL_FreeWAV(audio_buf);
}

void Audio::play_menu_sound(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    while(SOUND){
            while(!MENUSOUND) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            MENUSOUND = 0;
    }

}

void Audio::play_game_over_sound(){

        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
        Uint8* audio_buf;
        Uint32 audio_len;

        while(SOUND){
            while(!GAMEOVERSOUND) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            GAMEOVERSOUND = 0;
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);

        }
}
