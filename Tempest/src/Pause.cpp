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
void Pause::update() { }
    

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

    render_color(renderer, YELLOW, 255);

    TextRenderer::draw_text(renderer, "PAUSE", WIDTH/2 - 100,  HEIGHT/6, 2., 2);
    TextRenderer::draw_text(renderer, "Press space to return to the game", WIDTH/2 - 250, 4*HEIGHT/5 - 150, 1., 2);
    TextRenderer::draw_text(renderer, "Press escape to go back to the main menu", WIDTH/2 - 275, 4*HEIGHT/5 - 70, 1., 2);

    // score
    render_color(renderer, std::move(this->game_ptr->getLevel()->get_score_color()));
    TextRenderer::draw_text(renderer,  std::move("Score: " + std::to_string(player->get_score())), 30, 50, 0.6, 2);

    // Player Name
    TextRenderer::draw_text(renderer, std::move(player->get_name()), 30 , 100, 0.6, 2);
    TextRenderer::draw_life(renderer, player->get_life_point(), 30, 150, std::move(player->get_color().get_name()));

    // niveau
    render_color(renderer, this->game_ptr->getMap()->get_color());
    TextRenderer::draw_text(renderer, std::move("Level " + std::to_string(this->game_ptr->getLevel()->get_current_level())), 30, 200, 0.6, 2);

    // màj du rendu
    render_present(renderer);
}