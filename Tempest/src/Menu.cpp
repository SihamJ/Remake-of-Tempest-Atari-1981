#include "Menu.hpp"

extern int WIDTH;
extern int HEIGHT;

Menu::Menu(std::shared_ptr<Game> g) : game_ptr(g) {}
Menu::~Menu() {}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * en mode main menu
 * 
 */
void Menu::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            this->game_ptr->setIsRunning(false);
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_SPACE) {
                this->game_ptr->getTimer()->reset_clock(clock_list::level);
                this->game_ptr->getTimer()->reset_clock(clock_list::current_transition);
                this->game_ptr->set_level(this->chosen_level);
                this->game_ptr->setStart(true);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) { 
                this->game_ptr->setIsRunning(false);
            }
            break;
        }
        case SDL_MOUSEWHEEL: {
            if(event.wheel.y > 0) // scroll up
            {
                this->chosen_level = (this->chosen_level + 1) % 100 + 1;
            }
            else if(event.wheel.y < 0) // scroll down
            {
                this->chosen_level = ((this->chosen_level - 1) + 99) % 100;
            }
        }
        default:
            break;
    }
}

/**
 * @brief On met à jour tous les éléments -> tous les TICK millisecondes
 * en mode main menu
 * 
 */
void Menu::update() { this->game_ptr->join_threads(); }
    

/**
 * @brief On clear + draw tous les éléments du main menu
 * 
 */
void Menu::render() {
    std::shared_ptr<SDL_Renderer> renderer = this->game_ptr->getRenderer();

    // clear la fenêtre en noir
    clear_renderer(renderer, BLACK);
    render_image(renderer, "images/logo.bmp", 1078, 427, WIDTH/2, HEIGHT/2, WIDTH/4, HEIGHT/4, 0, NULL);
    render_color(renderer, "255220220", 255);

    TextRenderer::draw_text(renderer, "PRESS SPACE TO START", WIDTH/2 - 200, 4*HEIGHT/5, 1, 2);
    TextRenderer::draw_text(renderer, "Scroll to chose your level: " + std::to_string(this->chosen_level), WIDTH/2 - 235, 4*HEIGHT/5 + 60, 1, 2);
    TextRenderer::draw_text(renderer, "EXIT: ESCAPE", 10, 50, 0.5, 2);
    
    // màj du rendu
    render_present(renderer);
}