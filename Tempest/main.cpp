#include <Game.hpp>
extern int WIDTH;
extern int HEIGHT;
#include <Pause.hpp>
#include <GameOver.hpp>
#include <Menu.hpp>
#include <Audio.hpp>
// #define SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED_DISPLAY(0)
int SOUND = 0;
int MENU = 1;
int GAMEOVER = 0;
int SHOOT = 0;
int ENEMYSHOOT = 0;
int SUPERZAPPER = 0;
int FLIPPERATTACK = 0;
int PLAYERTOUCHE = 0;
int LEVEL = 0;
int SCORE = 0;
int PAUSE = 0;
int SOUND2 = 1;

void menu();
void gameover();
void shoot();
void enemy_shoot();
void superzapper();
void player_touche();
void next_level();
void score();

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
    th.emplace_back(menu);
    th.emplace_back(gameover);
    th.emplace_back(shoot);
    //th.emplace_back(enemy_shoot);
    th.emplace_back(superzapper);
    //th.emplace_back(player_touche);
    th.emplace_back(next_level);
    th.emplace_back(score);

    // boucle principal
    while (game->running()) {

        while(!game->getStart() && game->running()) {
            main_menu->handle_events();
            main_menu->update();
            main_menu->render();
        }
        

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
            game_over->handle_events();
            game_over->update();
            game_over->render();
        }
        
    }

    SOUND = 0;

    for(auto t = th.begin(); t!=th.end(); t++){
        (*t).join();
    }
    game->clean();
    return 0;
}

void menu(){
    Audio audio = Audio();
    audio.menu();
}

void gameover(){
    Audio audio = Audio();
    audio.gameover();
}

void shoot(){
    Audio audio = Audio();
    audio.shoot();                           
}

void enemy_shoot(){
    Audio audio = Audio();
    audio.enemy_shoot();                           
}

void superzapper(){
    Audio audio = Audio();
    audio.superzapper();
}

void player_touche(){
    Audio audio = Audio();
    audio.player_touche();
}

void next_level(){
    Audio audio = Audio();
    audio.next_level();
}

void score(){
    Audio audio = Audio();
    audio.inc_score();
}