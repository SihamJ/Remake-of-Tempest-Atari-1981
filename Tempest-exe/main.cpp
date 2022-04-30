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
    audio.play_menu_sound();
}

void play_game_over(){
    Audio audio = Audio();
    audio.play_game_over_sound();
}

void play_shoot(){
    Audio audio = Audio();
    audio.shoot(100);                           
}

int main(int argc, char** argv) {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::unique_ptr<Pause> pause = std::make_unique<Pause>(game);
    std::unique_ptr<GameOver> game_over = std::make_unique<GameOver>(game);
    std::unique_ptr<Menu> main_menu = std::make_unique<Menu>(game);



    int nbth = std::thread::hardware_concurrency();
    std::vector<std::thread> th;
    th.reserve(nbth);

    game->init("Tempest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN_DESKTOP, 
                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);


    // doit être fait après SDL INIT AUDIO
    th.emplace_back(play_menu);
    th.emplace_back(play_game_over);
    th.emplace_back(play_shoot);
    

    // boucle principal
    while (game->running()) {

        while(!game->getStart() && game->running()) {
            MENUSOUND = 1;
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

        
        while (game->getGameOver() && !game->getStart() && game->running()) {
            GAMEOVERSOUND=1;
            game_over->handle_events();
            game_over->update();
            game_over->render();
        }
        GAMEOVERSOUND=0;
    }

    SOUND = 0;

    for(auto t = th.begin(); t!=th.end(); t++){
        (*t).join();
    }
    game->clean();
    return 0;
}