#include "Audio.hpp"

extern int SOUND;
extern int MENU;
extern int GAMEOVER;
extern int SHOOT;
extern int ENEMYSHOOT;
extern int SUPERZAPPER;
extern int FLIPPERATTACK;
extern int PLAYERTOUCHE;
extern int SCORE;
extern int LEVEL;
extern int PAUSE;

Audio::Audio(){
    
}

Audio::~Audio(){}

void Audio::shoot(){

    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV_RW( SDL_RWFromFile("Audio/shoot.wav", "rb"), 1, &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }
        
    while(SOUND){
        while(!SHOOT){ if(!SOUND) break ;}
        if(!SOUND) break;
        device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), NULL, 0);
        
        int success = SDL_QueueAudio(device, audio_buf, audio_len);
        SDL_PauseAudioDevice(device, SDL_FALSE);
        SDL_Delay(200);
        SDL_PauseAudioDevice(device, SDL_TRUE);
        SDL_CloseAudioDevice(device);
        SHOOT=0;
    }
    SDL_FreeWAV(audio_buf);
}

void Audio::menu(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV( "Audio/menu.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!MENU) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            while(MENU);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            MENU = 0;
    }
    }

void Audio::gameover(){

        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
        Uint8* audio_buf;
        Uint32 audio_len;

        if( SDL_LoadWAV("Audio/gameover3.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

        while(SOUND){
            while(!GAMEOVER) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(5000);
            GAMEOVER = 0;
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
        }
}

void Audio::player_touche(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/collision2.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!PLAYERTOUCHE) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            PLAYERTOUCHE = 0;
    }

}

void Audio::inc_score(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/score.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!SCORE) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            SCORE = 0;
    }
}

void Audio::superzapper(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/superzapper.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!SUPERZAPPER) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(2000);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            SUPERZAPPER = 0;
    }

}

void Audio::flipper_attack(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/flipper_attack.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!FLIPPERATTACK) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(3000);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            FLIPPERATTACK = 0;
    }

}

void Audio::next_level(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/next_level.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!LEVEL) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(2000);
            SDL_PauseAudioDevice(device, SDL_TRUE);
           SDL_CloseAudioDevice(device);
            LEVEL = 0;
    }

}

void Audio::enemy_shoot(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/retro.wav",  &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!ENEMYSHOOT) if(!SOUND) break;
            if(!SOUND) break;
            device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0);
            int success = SDL_QueueAudio(device, audio_buf, audio_len);
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            ENEMYSHOOT = 0;
    }
}