#include <GameOver.hpp>

extern int WIDTH;
extern int HEIGHT;

GameOver::GameOver(std::shared_ptr<Game> g) : game_ptr(g) {}
GameOver::~GameOver() {}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * en mode pause
 * 
 */
void GameOver::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            this->game_ptr->setIsRunning(false);
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                this->game_ptr->setGameOver(false);
            }
            break;
        }
        default:
            break;
    }
}

/**
 * @brief On met à jour tous les éléments -> tous les TICK millisecondes
 * en mode pause
 * 
 */
void GameOver::update() { }
    

/**
 * @brief On clear + draw tous les éléments
 * en mode pause
 * 
 */
void GameOver::render() {
    std::shared_ptr<SDL_Renderer> renderer = this->game_ptr->getRenderer();
    std::shared_ptr<Player> player = this->game_ptr->getPlayer();

    clear_renderer(renderer, BLACK);

    if(render_image(renderer, "./images/gameover.bmp", 347, 63, 347,63 , WIDTH/2 - 173, HEIGHT/3, 0, NULL))
        return;

    render_color(renderer, WHITE, 255);
    TextRenderer::draw_text(renderer, std::move(this->game_ptr->getMsgGameOver()), WIDTH/2 - 160, HEIGHT/3 + 100, 1, 2);
    TextRenderer::draw_text(renderer, "PRESS ESCAPE TO GO BACK TO MAIN MENU", WIDTH/2 - 330, HEIGHT/3 + 170, 1, 2);
    // màj du rendu
    render_present(renderer);
}