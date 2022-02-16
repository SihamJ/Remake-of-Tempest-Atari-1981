#include "../headers/Game.hpp"

// #define SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED_DISPLAY(0)


Game *game = nullptr;

int main(int argc, char** argv) {
    game = new Game();

    // 480 et 420 à la place de windowpos_centered 
    // psq la fenêtre s'affiche entre mes deux écrans chez moi
    game->init("Tempest", 480, 420, // SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                800, 600, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI, 
                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    
    // boucle principal
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}