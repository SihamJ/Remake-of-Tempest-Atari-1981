#include "Pause.hpp"

extern int WIDTH;
extern int HEIGHT;

Pause::Pause(std::shared_ptr<Game> g) : game_ptr(g) {}
Pause::~Pause() {}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * en mode pause
 * 
 */
void Pause::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            this->game_ptr->setIsRunning(false);
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_SPACE) {
                this->game_ptr->setPause(false);
                this->game_ptr->getTimer()->unpause_clock(clock_list::level);
                this->game_ptr->getTimer()->unpause_clock(clock_list::current_transition);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                this->game_ptr->setPause(false);
                this->game_ptr->setStart(false);
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
void Pause::update() { this->game_ptr->join_threads();  }
    

/**
 * @brief On clear + draw tous les éléments
 * en mode pause
 * 
 */
void Pause::render() {
    std::shared_ptr<SDL_Renderer> renderer = this->game_ptr->getRenderer();
    std::shared_ptr<Player> player = this->game_ptr->getPlayer();

    // clear la fenêtre en noir
    clear_renderer(renderer, BLACK);

    render_color(renderer, WHITE, 255);

    TextRenderer::draw_text(renderer, "PAUSE", WIDTH/2,  4*HEIGHT/5 , 2., 2, true);
    TextRenderer::draw_text(renderer, "PRESS SPACE TO RETURN TO THE GAME", WIDTH/2, 4*HEIGHT/5 - 150, 1., 2, true);
    TextRenderer::draw_text(renderer, "PRESS ESCAPE TO GO BACK TO MAIN MENU", WIDTH/2, 4*HEIGHT/5 - 70, 1., 2, true);

    // score
    render_color(renderer,this->game_ptr->getLevel()->get_score_color());
    TextRenderer::draw_text(renderer,  "SCORE: " + std::to_string(player->get_score()), WIDTH/3, 100, 1, 2, true);

    // Player Name
    TextRenderer::draw_text(renderer, player->get_name(), WIDTH/2 , 100, 1, 2, true);
    TextRenderer::draw_life(renderer, player->get_life_point(), WIDTH/3, 150, player->get_color().get_name());

    // niveau
    render_color(renderer, this->game_ptr->getMap()->get_color());
    TextRenderer::draw_text(renderer, "LEVEL " + std::to_string(this->game_ptr->getLevel()->get_current_level()), WIDTH/2, HEIGHT/2, 3, 2, true);

    // màj du rendu
    render_present(renderer);
}