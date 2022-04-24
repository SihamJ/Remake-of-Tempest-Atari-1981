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

        this->textRenderer = TextRenderer();
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
                Tunel h = vh[player.get_n_hall()];

                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(h));
                // ajoute le point au vecteur qui répertorie tous les missiles
                vm.push_back(m);
                break;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                setPause(getPause() ? false : true);
            }
            break;
        }
        case SDL_MOUSEWHEEL: {
            if (getPause()) break;
            if(event.wheel.y > 0) // scroll up
            {
                player.decr_n_hall(map->get_nb_hall(), map->get_hall((player.get_n_hall() -1 + map->get_nb_hall())%map->get_nb_hall()));
            }
            else if(event.wheel.y < 0) // scroll down
            {
                player.incr_n_hall(map->get_nb_hall(), map->get_hall( (player.get_n_hall()+1) % map->get_nb_hall()));
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

    if (getPause()) {
        return;
    }

    // Passer au niveau suivant ?

    if (this->timer->get_clock(clock_list::level) > LEVEL_TIME){
        this->isTransitioning = true;
        this->timer->reset_clock(clock_list::level);
        this->next_level();
        return;
    }
    
    // Ajout de points au centre jusqu'aux extrémités de l'octogone
    // à des temps aléatoires < à 40000 millisecondes entre chacun
    // sur des couloirs aléatoires

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
                Spikers * enemy_spiker = dynamic_cast<Spikers*>(&(*e));
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
        for (int i = 0; i<vm.size(); i++) {
            if (vm[i]->get_closer()) {
                vm.erase(vm.begin()+i);
            }
            else if (!vm[i]->getEnemy()) {
                for (auto e : enemies) {
                    if (e->get_name().compare("spikers") == 0) {
                        if (e->get_hall() == vm[i]->get_hall()) {
                            Spikers * enemy_spiker = dynamic_cast<Spikers*>(&(*e));
                            if (enemy_spiker == nullptr)
                                return;

                            // detruit le missile si il atteint la ligne verte du spiker + diminue la ligne verte du spiker
                            double dist1 = vm[i]->get_pos().euclideanDistance(e->get_hall().get_big_line().inLine(0.5));
                            double dist2 = e->get_hall().get_big_line().inLine(0.5).euclideanDistance(enemy_spiker->get_line_limit().inLine(0.5));

                            if (dist1 > dist2) {
                                vm.erase(vm.begin()+i);
                                enemy_spiker->decrease_random_p();
                                enemy_spiker->update_line_limit();
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i<enemies.size(); i++) {
            long double h0, d, z, h;
            bool backwards = false;

            std::shared_ptr<Spikers> s = std::dynamic_pointer_cast<Spikers>(enemies.at(i));

            if( s != NULL && s->get_state() == 1){
                // h0 = s->get_dest().length() / s->get_start().length();
                // d = s->get_start().inLine(0.5).euclideanDistance(s->get_dest().inLine(0.5));
                // z = s->get_center().euclideanDistance(s->get_dest().inLine(0.5));

                h0 = s->get_hall().get_small_line().length() / s->get_limit().length();
                d = s->get_hall().get_small_line().inLine(0.5).euclideanDistance(s->get_limit().inLine(0.5));
                z = s->get_center().euclideanDistance(s->get_hall().get_small_line().inLine(0.5));
                backwards = true;
            }

            else{
                h0 = enemies.at(i)->get_start().length() / enemies.at(i)->get_dest().length(); 
                d = enemies.at(i)->get_start().inLine(0.5).euclideanDistance(enemies.at(i)->get_dest().inLine(0.5));
                z = enemies.at(i)->get_center().euclideanDistance(enemies.at(i)->get_dest().inLine(0.5));
            }
            
            h = this->level->get_h(h0, d, z, backwards);

            if (enemies[i]->get_closer(h)) {
                enemies.erase(enemies.begin()+i);
            }
        }

        // collision entre missile et player
        // Line  l1_player{ player.get_lines().at(0)};
        // Line l2_player{ player.get_lines().at(3)};

        // int x1, x2, x3, x4, y1, y2, y3, y4;
        // x1 = static_cast<int>(l1_player.get_p0().get_x());
        // y1 = static_cast<int>(l1_player.get_p0().get_y());
        // x2 = static_cast<int>(l1_player.get_p1().get_x());
        // y2 = static_cast<int>(l1_player.get_p1().get_y());

        // x3 = static_cast<int>(l2_player.get_p0().get_x());
        // y3 = static_cast<int>(l2_player.get_p0().get_y());
        // x4 = static_cast<int>(l2_player.get_p1().get_x());
        // y4 = static_cast<int>(l2_player.get_p1().get_y());
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

    render_color(std::move(map->get_color()));
    map->draw(renderer);

    render_color(YELLOW, 255);

    map->get_hall(player.get_n_hall()).draw(renderer);

    render_color(std::move(level->get_player_color()));    
    player.draw(renderer);

   // this->score.draw(renderer, 120);
    // dessine tous ce qui doit être affiché
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




    render_color(YELLOW, 255);
    
    this->textRenderer.draw(renderer, this->player.get_score(), WIDTH/4, 30, "YELLOW");

    this->textRenderer.draw(renderer, this->player.get_life_point(), 3*WIDTH/4, 30, "LIGHT_BLUE");
    this->textRenderer.draw(renderer, this->level->get_current_level(), WIDTH/2, 30, "LIGHT_BLUE");
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
    render_color(BLACK, 255);
    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }
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
    this->player.set_n_hall(0);
    this->player.build();
    
}


bool Game::running() { return this->isRunning; }
bool Game::transitioning() { return this->isTransitioning; }

bool Game::getPause() { return this->pause; }
void Game::setPause(bool pause) { this->pause = pause; }