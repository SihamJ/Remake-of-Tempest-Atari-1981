#include <Game.hpp>
extern int WIDTH;
extern int HEIGHT;
#include <Pause.hpp>
#include <GameOver.hpp>
#include <Menu.hpp>
#include <Audio.hpp>
// #define SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED_DISPLAY(0)
int SOUND = 1;
int MENUSOUND = 0;
int GAMEOVERSOUND = 0;
int SHOOTSOUND = 0;

void play_menu(){
    Audio audio = Audio();
    audio.menu_sound();
}

void play_game_over(){
    Audio audio = Audio();
    audio.game_over_sound();
}

void play_shoot(){
    Audio audio = Audio();
    audio.shoot(20);                           
}

int main(int argc, char** argv) {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::unique_ptr<Pause> pause = std::make_unique<Pause>(game);
    std::unique_ptr<GameOver> game_over = std::make_unique<GameOver>(game);
    std::unique_ptr<Menu> main_menu = std::make_unique<Menu>(game);
    bool menu = false;
    bool gameover = false;
    int nbth = std::thread::hardware_concurrency();
    std::vector<std::thread> th;
    th.reserve(nbth);
    //th.emplace_back(play_menu);
    // th.emplace_back(play_game_over);
    // th.emplace_back(play_shoot);

    SDL_AudioSpec spectre;

    SDL_memset(&(spectre), 0, sizeof(spectre));
    spectre.freq = 96000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spectre.format = AUDIO_F32SYS;
    spectre.channels = 1;
    spectre.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
    spectre.callback = [](void* param, Uint8* stream, int len)

    {
        // Envoyez les données dans notre buffer...
        int samples = len / sizeof(float); // 4096

        for (auto i = 0; i < samples; i++)
        {   
            reinterpret_cast<float*>(stream)[i] = 0.5 * SDL_sinf(2 * M_PI * i / 1000);
        }
    };

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0), 0, &(spectre), &(spectre), SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    SDL_PauseAudioDevice(device, SDL_FALSE);
    for(;;);


    game->init("Tempest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL, 
                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    // boucle principal


    while (game->running()) {


        MENUSOUND = 1;
        while(!game->getStart() && game->running()) {
            
            main_menu->handle_events();
            main_menu->update();
            main_menu->render();
        }
        MENUSOUND = 0;

        while(!game->getGameOver() && game->getStart() && game->running()) {
            
            
            while(game->getPause() && !game->getGameOver() && game->getStart() && game->running()) {
                pause->handle_events();
                pause->update();
                pause->render();
            }

            while (!game->getPause() && !game->getGameOver() && game->getStart() && game->running()) {
                game->handle_events();
                game->update();
                game->render();
            }

        }

        GAMEOVERSOUND=1;
        while (game->getGameOver() && !game->getStart() && game->running()) {
            
            game_over->handle_events();
            game_over->update();
            game_over->render();
        }
        GAMEOVERSOUND=0;
    }

    SOUND = 0;

    for(auto t = th.begin(); t!=th.end(); t++){
        (*t).detach();
    }

    game->clean();
    return 0;
}