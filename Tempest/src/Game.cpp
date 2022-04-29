#include <Game.hpp>


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
void Game::init(std::string title, int xpos, int ypos, int flagsWindow, int flagsRenderer) {

    if (init_sdl(SDL_INIT_VIDEO) == 0) {

        window = create_window(title, xpos, ypos, flagsWindow);
        renderer = create_renderer(window, -1, flagsRenderer);

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
        this->player = Player(0, std::move(map->get_hall(0)), std::move(this->level->get_player_color()));
        // récupère le point central de la Map
        center.set_point( map->get_center().get_x(), map->get_center().get_y());

        vh = map->get_hall_list();
        isRunning = true;
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
                Tunel h = vh.at(player.get_n_hall());

                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(h));
                // ajoute le point au vecteur qui répertorie tous les missiles
                vm.push_back(std::move(m));
                break;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                setPause(true);
                // On met en pause les timer de passage au niveau suivant et de transition courante s'il y en une
                this->timer->pause_clock(clock_list::level);
                this->timer->pause_clock(clock_list::current_transition);
            }
            if(event.key.keysym.sym == SDLK_RIGHT)
                player.decr_n_hall ( std::move (map->get_hall (player.get_n_hall () - 1)) );

            if(event.key.keysym.sym == SDLK_LEFT)
                player.incr_n_hall ( std::move (map->get_hall (player.get_n_hall () + 1)) );

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
                player.decr_n_hall ( std::move(map->get_hall ( player.get_n_hall () - 1)));
            }
            else if(event.wheel.y < 0) // scroll down
            {
                //std::cout << "scroll down" << std::endl;
                player.incr_n_hall ( std::move( map->get_hall ( player.get_n_hall () + 1)));
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
    
    std::mt19937 gen(this->rd());
    std::uniform_int_distribution<int> random (0, 100000);

    int i = random(gen);

    if ( this->timer->get_clock(clock_list::enemies) > i) {

        this->timer->reset_clock(clock_list::enemies);

        std::shared_ptr<Enemy> enemy = std::move(this->level->new_enemy());

        // un couloir aléatoire parmis les couloirs de la map
        Tunel hDest = vh.at(random(gen) % vh.size());
        
        //we set the enemy in its corresponding Hall and calculate other geometric parameters
        enemy->set(std::move(hDest));

        // faux si y a déjà un spiker sur le couloir
        bool enemy_valid = true;

        for (auto e : enemies) {
            // pour éviter d'avoir deux spikers dans le même couloir. On utilise l'overload de l'opérateur == sur Tunel, Line et Point.
            if (e->get_name().compare("spikers") == 0 && e->get_hall() == enemy->get_hall()) {
                enemy_valid = false;
                break;
            }
        }

        if (enemy_valid)
            enemies.push_back(std::move(enemy));
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
                    m->set_enemy();
                    vm.push_back(std::move(m));
                    enemy_spiker->set_state(-1);
                }
            }
        }

        // collisions.clear();

        timer->reset_clock(clock_list::update);
        // Rapproche tous les missiles de leur destination
        // détruit le missile si il a atteint sa cible
        
        for (auto it = vm.begin(); it != vm.end(); it++) {

            bool cond = false;
            if ((*it)->get_closer()) {
                if ((*it)->get_enemy() && this->player.get_hall() == (*it)->get_hall()) {
                    if(this->player.decr_life_point()){

                        this->setGameOver(true);
                        this->setStart(false);
                        this->game_over_msg = std::string("You Lost All Your Life Points");
                        return;
                    }
                }
                vm.erase(it--);
                continue;
            }

            else if (!(*it)->get_enemy()) {

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
            
            // si c'est un flipper, on check son état (entrain de flipper, va flipper, ou ne rien faire)
            if( f!= NULL && f->get_state() == 1 && !f->flipping() && f->get_will_flip()){
                
                // flip aléatoirement à gauche ou à droite
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> random (0, 2);
                int nb_hall = random(gen);
                nb_hall = nb_hall == 0 ? 1 : -1;

                // si map ouverte (couloirs non collés), il faut vérifier les index de couloir
                if(this->map->get_open()){
                    if (f->get_hall().get_n_hall() + nb_hall >= this->map->get_nb_hall())
                        nb_hall = -1;
                    else if(f->get_hall().get_n_hall() + nb_hall < 0)
                        nb_hall = 1;
                }

                // on set le nouveau hall dans lequel le flipper va flipper
                f->set_next_hall(std::move(this->map->get_hall(f->get_hall().get_n_hall() + nb_hall)));
                // on determine l'angle entre le couloir actuel et le couloir suivant pour effectuer notre rotation
                f->set_next_angle(std::move(f->get_hall().get_angle(f->get_next_hall())));
            }

            // si c'est un spiker à l'état 1 (marche arrière), les paramètres d'homothétie sont différents
            if( s != NULL && s->get_state() == 1){

                h0 = s->get_hall().get_small_line().length() / s->get_limit().length();
                d = s->get_hall().get_small_line().inLine(0.5).euclideanDistance(s->get_limit().inLine(0.5));
                z = s->get_center().euclideanDistance(s->get_hall().get_small_line().inLine(0.5));
                backwards = true;
            }

            // Sinon même paramètres d'homothétie
            else {
                h0 = (*i)->get_start().length() / (*i)->get_dest().length(); 
                d = (*i)->get_start().inLine(0.5).euclideanDistance((*i)->get_dest().inLine(0.5));
                z = (*i)->get_center().euclideanDistance((*i)->get_dest().inLine(0.5));
            }
            
            // La génération du facteur h se fait à partir de la classe niveau car on fait varier la vitesse des ennemis selon le niveau
            h = this->level->get_h(h0, d, z, backwards);

            // Déplacement de l'ennemi et vérification s'il a atteint la périphérie
            if ((*i)->get_closer(h)) {
                // si flipper, et couloir player, game over
                if( f!=NULL && f->get_n_hall() == player.get_n_hall()){
                    this->setGameOver(true);
                    this->setStart(false);
                    game_over_msg = std::string("Killed by the Flipper");
                    return;
                }
                // si pas flipper, disparition de l'ennemi
                else if(f == NULL)
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
    clear_renderer(renderer, BLACK);

    if(this->isTransitioning){
        render_color(renderer, std::move(this->level->get_map_color()));
        this->textRenderer.draw_text(renderer,  "LEVEL " + std::to_string(this->level->get_current_level()), WIDTH/2-100, HEIGHT/3., 2, 3);
        render_present(renderer);
        return;
    }

    if (getPause()) { render_present(renderer); return;}
    render_color(renderer, std::move(map->get_color()));
    map->draw(renderer);

    if(this->level->get_current_level() < 17){
        render_color(renderer, YELLOW, 255);
        map->get_hall(player.get_n_hall()).draw(renderer);
    }

    render_color(renderer, std::move(level->get_player_color()));    
    player.draw(renderer);


    // Missiles 
    for (auto i : vm)
        i->draw(renderer);


    for (auto i : enemies){
        // on récupère la couleur de l'ennemi
        render_color(renderer, std::move(i->get_color()));
        i->draw(renderer);
    }

    // for (auto i : collisions){
    //     i.draw(renderer);
    // }

    render_color(renderer, std::move(this->level->get_score_color()));
    this->textRenderer.draw_text(renderer,  std::to_string(this->player.get_score()), 1*WIDTH/4, 50, 1, 2);

    // Player Name
    this->textRenderer.draw_text(renderer,  this->player.get_name(), WIDTH/2-60 , 50, 1, 2);

    this->textRenderer.draw_life(renderer, this->player.get_life_point(), 1*WIDTH/4, 70, this->player.get_color().get_name());

    render_color(renderer, std::move(this->map->get_color()));
    this->textRenderer.draw_text(renderer, std::to_string(this->level->get_current_level()), WIDTH/2-10, 110, 0.8, 2);
    
    if(this->superzapping){
        render_color(renderer, std::move(LIGHT_BLUE), 255);
        this->textRenderer.draw_text(renderer, "SUPERZAPPER!", WIDTH/3, HEIGHT/3, 2, 4);
    }
    
    // màj du rendu
    render_present(renderer);
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
    clear_renderer(renderer, BLACK);

    render_color(renderer, YELLOW, 255);

    this->textRenderer.draw_text(renderer, std::move("PAUSE"), WIDTH/2 - 70,  150, 1, 2);
    this->textRenderer.draw_text(renderer, std::move("Press escape to return to the game"), WIDTH/2 - 110, 200, 0.6, 2);

    // score
    render_color(renderer, std::move(this->level->get_score_color()));
    this->textRenderer.draw_text(renderer,  std::move("Score: " + std::to_string(this->player.get_score())), 30, 50, 0.6, 2);

    // Player Name
    this->textRenderer.draw_text(renderer, std::move(this->player.get_name()), 30 , 100, 0.6, 2);
    this->textRenderer.draw_life(renderer, this->player.get_life_point(), 30, 150, std::move(this->player.get_color().get_name()));

    // niveau
    render_color(renderer, this->map->get_color());
    this->textRenderer.draw_text(renderer, std::move("Level " + std::to_string(this->level->get_current_level())), 30, 200, 0.6, 2);

    // màj du rendu
    render_present(renderer);
}




void Game::next_level(){

    this->timer->reset_clock(clock_list::current_transition);
    this->isTransitioning = true;
    this->vm.clear();
    this->vh.clear();
    this->enemies.clear();
    this->level->next_level();
    this->map = std::move(level->get_map());
    this->player.clean();
    map->build_map();
    center.set_point(map->get_center().get_x(), map->get_center().get_y());
    vh = map->get_hall_list();
    this->player.set_hall(std::move(map->get_hall(0)));
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
    clear_renderer(renderer, BLACK);
    render_image(renderer, "images/logo.bmp", 1078, 427, WIDTH/2, HEIGHT/2, WIDTH/4, HEIGHT/4, 0, NULL);
    render_color(renderer, "255220220", 255);
    this->textRenderer.draw_text(renderer, "PRESS ESCAPE TO START", WIDTH/2 - 200, 4*HEIGHT/5, 1, 2);
    
    // màj du rendu
    render_present(renderer);
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

    clear_renderer(renderer, BLACK);

    if(render_image(renderer, "./images/gameover.bmp", 347, 63, 347,63 , WIDTH/2 - 173, HEIGHT/3, 0, NULL))
        return;

    render_color(renderer, "255205205", 255);
    this->textRenderer.draw_text(renderer, this->game_over_msg, WIDTH/2 - 160, HEIGHT/3 + 100, 1, 2);
    this->textRenderer.draw_text(renderer, std::move("PRESS ESCAPE TO GO BACK TO MAIN MENU"), WIDTH/2 - 330, HEIGHT/3 + 170, 1, 2);
    // màj du rendu
    render_present(renderer);
}

void Game::superzapper(bool all_enemies){

    this->superzapping = true;

    // superzapper animation, clock is popped after completion
    this->timer->reset_clock(clock_list::current_transition);
    
    // 1er superzapper détruit tous les ennemies
    if(all_enemies)
        this->enemies.clear();
    // 2eme superzapper détruit un seul ennemi aléatoirement
    else {
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> random (0, this->enemies.size());
        int i = random(gen);
        this->enemies.erase(this->enemies.begin()+i);
    }
}

/**
 * @brief Clean tout quand l'utilisateur a décidé de quitter le jeu
 * 
 */
void Game::clean() {
    quit_game(window, renderer);
}


bool Game::running() { return this->isRunning; }
bool Game::transitioning() { return this->isTransitioning; }
bool Game::getPause() { return this->pause; }
void Game::setPause(bool pause) { this->pause = pause; }
void Game::setGameOver(bool go) { this->game_over = go; }
bool Game::getGameOver() { return this->game_over; }
bool Game::getStart() { return this->start; }
void Game::setStart(bool start) { this->start = start; }