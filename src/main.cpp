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

    // SDL_Init(SDL_INIT_VIDEO);
    // std::cout << "SDL Init" << std::endl;

    // auto window = (sdl_shared<SDL_Window>(SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI)));
    //     if (window) {
    //         std::cout << "Window created" << std::endl;
    //     }

    // auto renderer = (sdl_shared(SDL_CreateRenderer(window.get(), -1,  SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)));
    //     if (renderer) {
    //         std::cout << "Renderer created" << std::endl;
    //     }
    // int i = 0;
    // bool isRunning = true;

    // while(isRunning){

    //     std::string path;
    //     path = static_cast<std::string>("images/flipper_") + static_cast<std::string>("RED") + static_cast<std::string>(".bmp"); 

    //     auto image = sdl_shared(SDL_LoadBMP(path.c_str()));

    //     if(!image)
    //     {
    //         SDL_Log("Erreur > %s", SDL_GetError());
    //         break;
    //     }

    //     SDL_Rect dest_rect = {10, 10, 40, 20};
    //     auto monImage = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));
    //     if (SDL_QueryTexture(monImage.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
    //         SDL_Log("Erreur > %s", SDL_GetError());
    //         break;
    //     }
    //     dest_rect.w = 40;
    //     dest_rect.h = 20;
    //     if (SDL_RenderCopyEx(renderer.get(), monImage.get(), NULL, &dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
    //         SDL_Log("Erreur > %s", SDL_GetError());
    //         break;
    //     }


    //     SDL_RenderPresent(renderer.get());

    //     SDL_Event event;
    //     SDL_PollEvent(&event);
    //     switch(event.type) {
    //         case SDL_QUIT: {
    //             isRunning = false;
    //             break;
    //             }
    //     }

    //     i++;
    // }



    // SDL_Quit();
    // return 0;
}