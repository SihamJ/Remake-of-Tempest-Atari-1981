#include <GameOver.hpp>

extern int WIDTH;
extern int HEIGHT;
extern int MENU;
extern int SOUND2;


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
                MENU = 1;
                this->game_ptr->setGameOver(false);
            }
            if(event.key.keysym.sym == SDLK_q){
                this->game_ptr->setIsRunning(false);
                break;
            }
            if(event.key.keysym.sym == SDLK_m){
                SOUND2 =  SOUND2 == 0 ? 1 : 0;
                break;
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
void GameOver::update() {  this->game_ptr->join_threads(); }
    

/**
 * @brief On clear + draw tous les éléments
 * en mode pause
 * 
 */
void GameOver::render() {
    std::shared_ptr<SDL_Renderer> renderer = this->game_ptr->getRenderer();
    std::shared_ptr<Player> player = this->game_ptr->getPlayer();

    clear_renderer(renderer, BLACK);

    if(render_image(renderer, "./images/gameover.bmp", 347, 63, 347,63 , WIDTH/2 - 347/2, HEIGHT/2 - 63/2, 0, NULL))
        return;

    render_color(renderer, WHITE, 255);
    TextRenderer::draw_text(renderer, "LEVEL: " + std::to_string(this->game_ptr->getLevel()->get_current_level()), WIDTH/2, HEIGHT/5, 1, 2, true);
    TextRenderer::draw_text(renderer, this->game_ptr->get_msg_game_over(), WIDTH/2, 3*HEIGHT/4, 1, 2, true);
    TextRenderer::draw_text(renderer, "PRESS ESCAPE TO GO BACK TO MAIN MENU", WIDTH/2, 3*HEIGHT/4 + 170, 1, 2, true);
    // màj du rendu
    render_present(renderer);
}