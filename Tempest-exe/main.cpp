#include <Game.hpp>
#include <Pause.hpp>
#include <GameOver.hpp>
#include <Menu.hpp>

// #define SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED_DISPLAY(0)



int main(int argc, char** argv) {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::unique_ptr<Pause> pause = std::make_unique<Pause>(game);
    std::unique_ptr<GameOver> game_over = std::make_unique<GameOver>(game);
    std::unique_ptr<Menu> main_menu = std::make_unique<Menu>(game);


    // 480 et 420 à la place de windowpos_centered 
    // psq la fenêtre s'affiche entre mes deux écrans chez moi
    game->init("Tempest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI, 
                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

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

    game->clean();

    return 0;
}