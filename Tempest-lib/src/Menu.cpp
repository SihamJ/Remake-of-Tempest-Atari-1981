#include "Menu.hpp"

extern int WIDTH;
extern int HEIGHT;
extern int MENU;
extern int SOUND2;

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
                MENU = 0;
                this->game_ptr->getTimer()->reset_clock(clock_list::level);
                this->game_ptr->getTimer()->reset_clock(clock_list::current_transition);
                this->game_ptr->set_level(this->chosen_level);
                this->game_ptr->setStart(true);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) { 
                MENU = 0;
                this->game_ptr->setIsRunning(false);
            }
            if(event.key.keysym.sym == SDLK_m){
                SOUND2 =  SOUND2 == 0 ? 1 : 0;
                break;
            }
            break;
        }
        case SDL_MOUSEWHEEL: {
            if(event.wheel.y > 0) // scroll up
            {
                this->chosen_level = (this->chosen_level + 1) % 200 + 1;
            }
            else if(event.wheel.y < 0) // scroll down
            {
                this->chosen_level = ((this->chosen_level - 1) + 199) % 200;
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
    render_image(renderer, "images/logo.bmp", 1078, 427, 1078, 427, (WIDTH/2)-(1078/2), (HEIGHT/2)-(427/2), 0, NULL);
    render_color(renderer, "255220220", 255);

    TextRenderer::draw_text(renderer, "PRESS SPACE TO START", WIDTH/2, 4*HEIGHT/5, 1, 2, true);
    TextRenderer::draw_text(renderer, "SCROLL TO CHOSE YOUR LEVEL: " + std::to_string(this->chosen_level), WIDTH/2, 4*HEIGHT/5 + 60, 1, 2, true);
    TextRenderer::draw_text(renderer, "EXIT: ESCAPE", 10, 50, 0.5, 2, false);
    
    // màj du rendu
    render_present(renderer);
}