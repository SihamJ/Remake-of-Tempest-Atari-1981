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
extern int SOUND2;

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
        if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
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
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            while(MENU);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            MENU = 0;
    }
    SDL_FreeWAV(audio_buf);
}

void Audio::gameover(){

        SDL_AudioSpec spectre;
        SDL_AudioDeviceID device;
        Uint8* audio_buf;
        Uint32 audio_len;

        if( SDL_LoadWAV("Audio/gameover.wav", &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

        while(SOUND){
            while(!GAMEOVER) if(!SOUND) break;
            if(!SOUND) break;
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(5000);
            GAMEOVER = 0;
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
        }
        SDL_FreeWAV(audio_buf);
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
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            SCORE = 0;
    }
    SDL_FreeWAV(audio_buf);
}

void Audio::superzapper(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/supperzapper.wav",  &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!SUPERZAPPER) if(!SOUND) break;
            if(!SOUND) break;
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            SUPERZAPPER = 0;
    }
    SDL_FreeWAV(audio_buf);
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
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(2000);
            SDL_PauseAudioDevice(device, SDL_TRUE);
           SDL_CloseAudioDevice(device);
            LEVEL = 0;
    }
    SDL_FreeWAV(audio_buf);
}

void Audio::enemy_shoot(){
    SDL_AudioSpec spectre;
    SDL_AudioDeviceID device;
    Uint8* audio_buf;
    Uint32 audio_len;

    if( SDL_LoadWAV("Audio/enemy_shot.wav",  &spectre, &audio_buf, &audio_len) == NULL){
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    while(SOUND){
            while(!ENEMYSHOOT) if(!SOUND) break;
            if(!SOUND) break;
            if((device = SDL_OpenAudioDevice(nullptr, 0, &(spectre), nullptr, 0)) == 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            }
            if( SDL_QueueAudio(device, audio_buf, audio_len) < 0){
                SDL_Log("Erreur > %s", SDL_GetError());
                break;
            } 
            SDL_PauseAudioDevice(device, SDL_FALSE);
            SDL_Delay(200);
            SDL_PauseAudioDevice(device, SDL_TRUE);
            SDL_CloseAudioDevice(device);
            ENEMYSHOOT = 0;
    }
    SDL_FreeWAV(audio_buf);
}
