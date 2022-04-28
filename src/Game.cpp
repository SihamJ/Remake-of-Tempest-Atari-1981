#include "../headers/Game.hpp"


Game::Game() {}
Game::~Game() {}

/**
 * @brief Initialise le jeu
 * 
 * @param title titre de la fenêtre
 * @param xpos la position en abscisse de la fenêtre
 * @param ypos la position en ordonnée de la fenêtre
 * @param width la largeur de la fenêtre
 * @param height la hauteur de la fenêtre
 */
void Game::init(const char *title, int xpos, int ypos, int flagsWindow, int flagsRenderer) {

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		std::cout << "SDL Init" << std::endl;

        window = (sdl_shared<SDL_Window>(SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flagsWindow)));
        if (window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = (sdl_shared(SDL_CreateRenderer(window.get(), -1, flagsRenderer)));
        if (renderer) {
            std::cout << "Renderer created" << std::endl;
        }

        this->timer = std::make_unique<Timer>();
        
        // clock 1 game update
        this->timer->add_clock();
        // clock 2 pour enemies
        this->timer->add_clock();
        // clock 3 pour passer au niveau suivant
        this->timer->add_clock();
        // clock 4 pour animation courante
        this->timer->add_clock();

        this->level = std::make_shared<Level>(0);
        this->level->next_level();
        this->map = level->get_map();

        // construction de la map
        map->build_map();
        this->player = Player(0, map->get_hall(0), this->level->get_player_color());
         // récupère le point central de la Map
        center.set_point(map->get_center().get_x(), map->get_center().get_y());

        vh = map->get_hall_list();
        isRunning = true;

        std::cout << "done" << std::endl;


    }
    else {
        // si problème, le jeu doit s'arrêter
        isRunning = false;
    }
    
}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * 
 */
void Game::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_SPACE){
                // le couloir où le player se trouve
                //std::cout << "missile alliée" <<std::endl;
                Tunel h = vh[player.get_n_hall()];

                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(h));
                // ajoute le point au vecteur qui répertorie tous les missiles
                vm.push_back(m);
                break;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                setPause(true);
                this->timer->pause_clock(clock_list::level);
                this->timer->pause_clock(clock_list::current_transition);
            }
            if(event.key.keysym.sym == SDLK_RIGHT)
                player.decr_n_hall ( map->get_hall ( player.get_n_hall () - 1 ) );
            if(event.key.keysym.sym == SDLK_LEFT)
                player.incr_n_hall ( map->get_hall ( player.get_n_hall () + 1 ) );
            // TO DO:
            if(event.key.keysym.sym == SDLK_z){
                if( !this->superzapping && player.dec_superzapper()){
                    this->superzapper(player.get_superzapper()==0 ? false : true);
                }
            }
            break;
        }
        case SDL_MOUSEWHEEL: {
            if(event.wheel.y > 0) // scroll up
            {
                //std::cout << "scroll up" << std::endl;
                player.decr_n_hall ( map->get_hall ( player.get_n_hall () - 1 ) );
            }
            else if(event.wheel.y < 0) // scroll down
            {
                //std::cout << "scroll down" << std::endl;
                player.incr_n_hall ( map->get_hall ( player.get_n_hall () + 1 ) );
            }
        }
        default:
            break;
    }
}

/**
 * @brief On met à jour tous les éléments -> tous les TICK millisecondes
 * 
 */
void Game::update() {

    // Passer au niveau suivant ?

    if (!this->isTransitioning && this->timer->get_clock(clock_list::level) > LEVEL_TIME){
        this->isTransitioning = true;
        this->timer->reset_clock(clock_list::level);
        this->next_level();
        return;
    }

    if(this->isTransitioning && this->timer->get_clock(clock_list::current_transition) > TRANSISTION_TIME){
        this->isTransitioning = false;
        this->timer->reset_clock(clock_list::current_transition);
    }

    // on ne veut pas update le jeu avant de finir l'animation de transition
    else if(this->isTransitioning) return;

    if(this->superzapping && this->timer->get_clock(clock_list::current_transition) > SUPERZAPPER_TIME){
            this->superzapping = false;
    }
    

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random (0, 100000);

    int i = random(gen);

    if ( this->timer->get_clock(clock_list::enemies) > i) {
        // maj horloge
        this->timer->reset_clock(clock_list::enemies);
        generated=true;
        std::shared_ptr<Enemy> enemy = this->level->new_enemy();

        // un couloir aléatoire parmis les couloirs de la map
        Tunel hDest = vh[random(gen) % vh.size()];
        
        //instead of copying values, we move them by rvalue reference. They won't be needed afterwards.
        enemy->set(std::move(hDest));

        // faux si y a déjà un spiker sur le couloir
        bool enemy_valid = true;

        for (auto e : enemies) {
            if (e->get_name().compare("spikers") == 0 && e->get_hall() == enemy->get_hall()) {
                enemy_valid = false;
                break;
            }
        }

        if (enemy_valid)
            enemies.push_back(enemy);
    }
    // Si on a dépassé les TICK millisecondes, on update
    if (timer->get_clock(clock_list::update) > TICK) {

        for (auto e : enemies) {
            if (e->get_name().compare("spikers") == 0) {
                std::shared_ptr<Spikers> enemy_spiker = std::dynamic_pointer_cast<Spikers>(e);
                if (enemy_spiker == nullptr)
                    return;
                if (enemy_spiker->get_state() == 2) {
                    std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(enemy_spiker->get_hall()));
                    m->setEnemy();
                    vm.push_back(m);
                    enemy_spiker->setState(-1);
                }
            }
        }

        // collisions.clear();

        timer->reset_clock(clock_list::update);
        // Rapproche tous les missiles de leur destination
        // détruit le missile si il a atteint sa cible
        
        for (auto it = vm.begin(); it != vm.end(); it++) {
            std::cout << "missile" << std::endl;
            bool cond = false;
            if ((*it)->get_closer()) {
                if ((*it)->getEnemy() && this->player.get_hall() == (*it)->get_hall()) {
                    if(this->player.decr_life_point()){
                        std::cout << "decr lfie point " << std::endl;
                        this->setGameOver(true);
                        this->setStart(false);
                        return;
                    }
                }
                vm.erase(it--);
                continue;
            }

            else if (!(*it)->getEnemy()) {

                for (auto e = enemies.begin(); e!= enemies.end(); e++) {

                    // si missile et ennemi pas dans le meme hall on continue à l'ennemi suivant
                    if( (*it)->get_hall() != (*e)->get_hall())
                        continue;

                    std::shared_ptr<Spikers> enemy_spiker = std::dynamic_pointer_cast<Spikers>(*e);

                    // si le missile tue un ennemi, on sort de la boucle ennemies car le missile est détruit, on passe au missile qui suit
                    if( (enemy_spiker == nullptr || (enemy_spiker->get_state() != -1)) && (*e)->collides_with(*(*it))) {
                        this->player.incr_score((*e)->get_scoring());
                        vm.erase(it--);
                        enemies.erase(e--);
                        break;
                    }

                    // si on tire sur la ligne d'un spiker, on diminue la ligne
                    
                    if (enemy_spiker != nullptr && enemy_spiker->get_state() == -1) {
                        // detruit le missile si il atteint la ligne verte du spiker + diminue la ligne verte du spiker
                        double dist1 = (*it)->get_pos().euclideanDistance((*e)->get_hall().get_big_line().inLine(0.5));
                        double dist2 = (*e)->get_hall().get_big_line().inLine(0.5).euclideanDistance(enemy_spiker->get_line_limit().inLine(0.5));

                        if (dist1 > dist2) {
                            vm.erase(it--);
                            enemy_spiker->decrease_random_p();
                            enemy_spiker->update_line_limit();
                            break;
                        }
                    }
                }
            }

        }


        // déplacements ennemies
        for (auto i = enemies.begin(); i != enemies.end(); i++) {
            long double h0, d, z, h;
            bool backwards = false;

            std::shared_ptr<Spikers> s = std::dynamic_pointer_cast<Spikers>(*i);
            std::shared_ptr<Flippers> f = std::dynamic_pointer_cast<Flippers>(*i);

            // Test collision
            

            if( f!= NULL && f->get_state() == 1 && !f->flipping()){

                // std::random_device rd;  
                // std::mt19937 gen(rd());
                // std::uniform_int_distribution<int> random (-1, 0);

                f->set_next_hall(this->map->get_hall(f->get_hall().get_n_hall() + 1));
                f->set_next_angle(f->get_hall().get_angle(f->get_next_hall()));
            }

            if( s != NULL && s->get_state() == 1){

                h0 = s->get_hall().get_small_line().length() / s->get_limit().length();
                d = s->get_hall().get_small_line().inLine(0.5).euclideanDistance(s->get_limit().inLine(0.5));
                z = s->get_center().euclideanDistance(s->get_hall().get_small_line().inLine(0.5));
                backwards = true;
            }

            else {

                h0 = (*i)->get_start().length() / (*i)->get_dest().length(); 
                d = (*i)->get_start().inLine(0.5).euclideanDistance((*i)->get_dest().inLine(0.5));
                z = (*i)->get_center().euclideanDistance((*i)->get_dest().inLine(0.5));
            }
            
            h = this->level->get_h(h0, d, z, backwards);

            if ((*i)->get_closer(h)) {
                // si flipper, et couloir player, game over
                // if( f!=NULL && f->get_n_hall() == player.get_n_hall()){
                //     this->setGameOver(true);
                //     this->setStart(false);
                //     return;
                // }
                // // si pas flipper, disparition de l'ennemi
                // else if(f == NULL)
                    enemies.erase(i--);
            }
        }
    }
}

/**
 * @brief On clear + draw tous les éléments
 * 
 */
void Game::render() {
    // clear la fenêtre en noir
    render_color(BLACK, 255);
    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }

    if(this->isTransitioning){
        render_color(std::move(this->level->get_map_color()));
        this->textRenderer.draw_text(renderer,  "LEVEL " + std::to_string(this->level->get_current_level()), WIDTH/2-100, HEIGHT/3., 2, 3);
        SDL_RenderPresent(renderer.get());
        return;
    }

    if (getPause()) { SDL_RenderPresent(renderer.get()); return;}
    render_color(std::move(map->get_color()));
    map->draw(renderer);

    render_color(YELLOW, 255);

    map->get_hall(player.get_n_hall()).draw(renderer);

    render_color(std::move(level->get_player_color()));    
    player.draw(renderer);


//   Missiles 
    for (auto i : vm)
        i->draw(renderer);


    for (auto i : enemies){
        // on récupère la couleur de l'ennemi
        render_color(std::move(i->get_color()));
        i->draw(renderer);
    }

    // for (auto i : collisions){
    //     i.draw(renderer);
    // }

    render_color(std::move(this->level->get_score_color()));
    this->textRenderer.draw_text(renderer,  std::to_string(this->player.get_score()), 1*WIDTH/4, 50, 1, 2);

    // Player Name
    this->textRenderer.draw_text(renderer,  this->player.get_name(), WIDTH/2-60 , 50, 1, 2);

    this->textRenderer.draw_life(renderer, this->player.get_life_point(), 1*WIDTH/4, 70, this->player.get_color().get_name());


    render_color(this->map->get_color());
    this->textRenderer.draw_text(renderer, std::to_string(this->level->get_current_level()), WIDTH/2-10, 110, 0.8, 2);
    
    if(this->superzapping){
        render_color(LIGHT_BLUE, 255);
        this->textRenderer.draw_text(renderer, "SUPERZAPPER!", WIDTH/3, HEIGHT/3, 2, 4);
    }
    
    // màj du rendu
    SDL_RenderPresent(renderer.get());
}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * en mode pause
 * 
 */
void Game::handle_events_pause_mode() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                setPause(false);
                this->timer->unpause_clock(clock_list::level);
                this->timer->unpause_clock(clock_list::current_transition);
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
void Game::update_pause_mode() { }
    




/**
 * @brief On clear + draw tous les éléments
 * en mode pause
 * 
 */
void Game::render_pause_mode() {
    // clear la fenêtre en noir
    render_color(BLACK, 255);
    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }

    render_color(YELLOW, 255);

    this->textRenderer.draw_text(renderer, "PAUSE", WIDTH/2 - 70,  150, 1, 2);
    this->textRenderer.draw_text(renderer, "Press escape to return to the game", WIDTH/2 - 110, 200, 0.6, 2);

    // score
    render_color(std::move(this->level->get_score_color()));
    this->textRenderer.draw_text(renderer,  "Score: " + std::to_string(this->player.get_score()), 30, 50, 0.6, 2);

    // Player Name
    this->textRenderer.draw_text(renderer, this->player.get_name(), 30 , 100, 0.6, 2);
    this->textRenderer.draw_life(renderer, this->player.get_life_point(), 30, 150, this->player.get_color().get_name());

    // niveau
    render_color(this->map->get_color());
    this->textRenderer.draw_text(renderer, "Level " + std::to_string(this->level->get_current_level()), 30, 200, 0.6, 2);

    // màj du rendu
    SDL_RenderPresent(renderer.get());
}

/**
 * @brief Clean tout quand l'utilisateur a décidé de quitter le jeu
 * 
 */
void Game::clean() {
    SDL_DestroyWindow(window.get());
    SDL_DestroyRenderer(renderer.get());
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}


void Game::render_color(Color&& c){
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), c.get_a());
}


void Game::render_color(std::string color){
    Color c { "", std::move(color) };
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), 255);
}

void Game::render_color(std::string color, const int opacity){
    Color c { "", std::move(color), opacity };
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), opacity);
}


void Game::next_level(){
    std::cout << "next level" << std::endl;
    this->timer->reset_clock(clock_list::current_transition);
    this->isTransitioning = true;
    this->vm.clear();
    this->vh.clear();
    this->enemies.clear();
    this->level->next_level();
    this->map = level->get_map();
    this->player.clean();
    map->build_map();
    center.set_point(map->get_center().get_x(), map->get_center().get_y());
    vh = map->get_hall_list();
    this->player.set_hall(map->get_hall(0));
    this->player.build();
    this->player.set_superzapper(2);
    this->superzapping = false;
}

void Game::handle_events_main_menu() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                this->timer->reset_clock(clock_list::level);
                this->timer->reset_clock(clock_list::current_transition);
                setStart(true);
            }
            break;
        }
        default:
            break;
    }
}

void Game::update_main_menu() {}
void Game::render_main_menu() {
    // clear la fenêtre en noir
    render_color(BLACK, 255);
    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }

    render_color(YELLOW, 255);
    
    //this->textRenderer.draw_text(renderer, "MAIN MENU", WIDTH/2 - 70, 120, 1, 2);

    auto image = sdl_shared(SDL_LoadBMP("./images/logo.bmp"));
    auto surface = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));

    SDL_Rect dest_rect = {0, 0, 1078, 427};

    if (SDL_QueryTexture(surface.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    dest_rect.w = WIDTH/2;
    dest_rect.h = (dest_rect.h * WIDTH/1078)/2;
    dest_rect.x = WIDTH/4;
    dest_rect.y = HEIGHT/4;

    if (SDL_RenderCopyEx(renderer.get(), surface.get(), NULL, &dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    render_color("255220220", 255);
    this->textRenderer.draw_text(renderer, "PRESS ESCAPE TO START", WIDTH/2 - 200, 4*HEIGHT/5, 1, 2);
    
    // màj du rendu
    SDL_RenderPresent(renderer.get());
}

void Game::handle_events_game_over() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                setGameOver(false);
            }
            break;
        }
        default:
            break;
    }
}

void Game::update_game_over() {}
void Game::render_game_over() {
    // clear la fenêtre en noir
    render_color(BLACK, 255);
    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }

    render_color(YELLOW, 255);
    
    this->textRenderer.draw_text(renderer, "GAME OVER", WIDTH/2 - 70, 120, 1, 2);
    this->textRenderer.draw_text(renderer, "Press escape to go back to main menu !", WIDTH/2 - 230, 170, 1, 2);
    
    // màj du rendu
    SDL_RenderPresent(renderer.get());
}


bool Game::running() { return this->isRunning; }
bool Game::transitioning() { return this->isTransitioning; }

bool Game::getPause() { return this->pause; }
void Game::setPause(bool pause) { this->pause = pause; }
void Game::setGameOver(bool go) { this->game_over = go; }
bool Game::getGameOver() { return this->game_over; }

bool Game::getStart() { return this->start; }
void Game::setStart(bool start) { this->start = start; }


void Game::superzapper(bool all_enemies){
    std::cout<<"superzapper"<<std::endl;
    this->superzapping = true;

    // superzapper animation, clock is popped after completion
    this->timer->reset_clock(clock_list::current_transition);
    
    // 1er superzapper détruit tous les ennemies
    if(all_enemies)
        this->enemies.clear();
    // 2eme superzapper détruit un seul ennemi aléatoirement
    else {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> random (0, this->enemies.size());
        int i = random(gen);
        this->enemies.erase(this->enemies.begin()+i);
    }
}