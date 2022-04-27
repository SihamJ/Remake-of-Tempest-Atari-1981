#include "../headers/Game.hpp"

// #define SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED_DISPLAY(0)


std::unique_ptr<Game> game;

int main(int argc, char** argv) {
    game = std::make_unique<Game>();

    // 480 et 420 à la place de windowpos_centered 
    // psq la fenêtre s'affiche entre mes deux écrans chez moi
    game->init("Tempest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI, 
                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    int i = 0;
    // boucle principal

    while (game->running()) {

        while(!game->getStart() && game->running()) {
            game->handle_events_main_menu();
            game->update_main_menu();
            game->render_main_menu();
            i++;
        }

        while(!game->getGameOver() && game->getStart() && game->running()) {
        
            while(game->getPause() && !game->getGameOver() && game->getStart() && game->running()) {
                game->handle_events_pause_mode();
                game->update_pause_mode();
                game->render_pause_mode();
                i++;
            }

            while (!game->getPause() && !game->getGameOver() && game->getStart() && game->running()) {
                game->handle_events();
                game->update();
                game->render();
                i++;
            }

        }
        
        while (game->getGameOver() && !game->getStart() && game->running()) {
            game->handle_events_game_over();
            game->update_game_over();
            game->render_game_over();
            i++;
        }
    }

    game->clean();

    return 0;
}