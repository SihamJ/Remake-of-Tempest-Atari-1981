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
        // pr utiliser rand avec des valeurs randoms
        srand (time(NULL));

        this->textRenderer = TextRenderer();

        this->level = std::make_shared<Level>(1);

        this->level->next_level();
        this->map = level->get_map();

        // construction de la map
        map->build_map();

        render_color(level->get_map_color());

        map->draw(renderer);

        render_color(level->get_player_color());

        this->player = Player(0, map->get_hall(0), this->level->get_player_color());
        this->player.draw(renderer);

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
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_f) {
                player.decr_n_hall(map->get_nb_hall(), map->get_hall((player.get_n_hall() -1 + map->get_nb_hall())%map->get_nb_hall()));
            }
            if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_j) {
                player.incr_n_hall(map->get_nb_hall(), map->get_hall( (player.get_n_hall()+1) % map->get_nb_hall()));
            }
            if (event.key.keysym.sym == SDLK_SPACE){
                // le couloir où le player se trouve
                Tunel h = vh[player.get_n_hall()];

                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(h));
                // ajoute le point au vecteur qui répertorie tous les missiles
                vm.push_back(m);
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
 * 
 */
void Game::update() {
    
    // Ajout de points au centre jusqu'aux extrémités de l'octogone
    // à des temps aléatoires < à 40000 millisecondes entre chacun
    // sur des couloirs aléatoires
    if ( SDL_GetTicks() - clock_new_p > (rand()%100000)) {
        // maj horloge
        clock_new_p = SDL_GetTicks();

        std::shared_ptr<Enemy> enemy = this->level->new_enemy();

        // un couloir aléatoire parmis les couloirs de la map
        Tunel hDest = vh[rand() % vh.size()];
        
        //instead of copying values, we move them by rvalue reference. They won't be needed afterwards.
        enemy->set(std::move(hDest));

        enemies.push_back(enemy);
    }
    // Si on a dépassé les TICK millisecondes, on update
    if (SDL_GetTicks() - clock > TICK) {

        // collisions.clear();

        clock = SDL_GetTicks();
        // Rapproche tous les missiles de leur destination
        // détruit le missile si il a atteint sa cible
        for (int i = 0; i<vm.size(); i++) {
            if (vm[i]->get_closer()) {
                vm.erase(vm.begin()+i);
            }
            else {
                for (auto e : enemies) {
                    if (e->get_name().compare("spikers") == 0) {
                        if (e->get_hall() == vm[i]->get_hall()) {
                            Spikers * enemy_spiker = dynamic_cast<Spikers*>(&(*e));
                            if (enemy_spiker == nullptr)
                                return;
                            Line random_p = enemy_spiker->get_line_current_limit();
                            int x1 = random_p.get_p0().get_x();
                            int y1 = random_p.get_p0().get_y();
                            int x2 = random_p.get_p1().get_x();
                            int y2 = random_p.get_p1().get_y();

                            SDL_Rect r = e->get_rect();

                            printf("jsuis là\n");
                            if (SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2) == SDL_TRUE) {
                                printf("non ?\n");
                                vm.erase(vm.begin()+i);
                                enemy_spiker->decrease_random_p();
                                enemy_spiker->update_line_limit();
                            }
                        }
                    }
                }
                // test si y a collision entre missiles alliés et ennemies

                // SDL_Rect r_missile;
                // r_missile.w = vm[i]->get_width();
                // r_missile.h = vm[i]->get_height();
                // r_missile.x = vm[i]->get_x();
                // r_missile.y = vm[i]->get_y();
               
                // for (int j = 0; j<enemies.size(); j++) {
                //     SDL_Rect r_enemy;
                //     r_enemy.w = enemies[j]->get_rect().at(0).euclideanDistance(enemies[j]->get_rect().at(1));
                //     r_enemy.h = enemies[j]->get_rect().at(1).euclideanDistance(enemies[j]->get_rect().at(2));
                //     r_enemy.x = enemies[j]->get_center().get_x();
                //     r_enemy.y = enemies[j]->get_center().get_y();

                //     SDL_Rect result;
                //     if (SDL_IntersectRect(&r_enemy, &r_missile, &result)){
                //         // Collision c { Point(result.x, result.y), Color(PURPLE), 2.0};
                //         // c.build();
                //         // render_color(PURPLE);
                //         // collisions.push_back(c);
                //         player.incr_score(enemies.at(j)->get_scoring());
                //         std::cout << "score: " << player.get_score() << std::endl;

                //         enemies.erase(enemies.begin()+j);
                //         vm.erase(vm.begin()+i);
                //         break;
                //     }
                // }
            }
        }

        for (int i = 0; i<enemies.size(); i++) {
            long double h0 = enemies.at(i)->get_speed();
            long double d = enemies.at(i)->get_hall().get_small_line().inLine(0.5).euclideanDistance(enemies.at(i)->get_hall().get_big_line().inLine(0.5));
            long double z = enemies.at(i)->get_center().euclideanDistance(enemies.at(i)->get_hall().get_big_line().inLine(0.5));
            long double h = this->level->get_h(h0, d, z);
            if (enemies[i]->get_closer(h)) {
                enemies.erase(enemies.begin()+i);
            }
        }

        // collision entre missile et player
        Line  l1_player{ player.get_lines().at(0)};
        Line l2_player{ player.get_lines().at(3)};

        int x1, x2, x3, x4, y1, y2, y3, y4;
        x1 = static_cast<int>(l1_player.get_p0().get_x());
        y1 = static_cast<int>(l1_player.get_p0().get_y());
        x2 = static_cast<int>(l1_player.get_p1().get_x());
        y2 = static_cast<int>(l1_player.get_p1().get_y());

        x3 = static_cast<int>(l2_player.get_p0().get_x());
        y3 = static_cast<int>(l2_player.get_p0().get_y());
        x4 = static_cast<int>(l2_player.get_p1().get_x());
        y4 = static_cast<int>(l2_player.get_p1().get_y());

        // for (int j = 0; j<enemies.size(); j++) {
        //     SDL_Rect r_enemy;
        //     r_enemy.w = enemies[j]->get_rect().at(0).euclideanDistance(enemies[j]->get_rect().at(1));
        //     r_enemy.h = enemies[j]->get_rect().at(1).euclideanDistance(enemies[j]->get_rect().at(2));
        //     r_enemy.x = enemies[j]->get_center().get_x();
        //     r_enemy.y = enemies[j]->get_center().get_y();

        //     // collision missile et player
        //     if (SDL_IntersectRectAndLine(&r_enemy, &x1, &y1, &x2, &y2) 
        //             || SDL_IntersectRectAndLine(&r_enemy, &x3, &y3, &x4, &y4)) 
        //         {
        //             std::cout << "collision player enemy" << std::endl;
        //             if(player.decr_life_point()){
        //                 std::cout << "GAME OVER" << std::endl;
        //                 this->isRunning = false;
        //         }
        //     }
        // }
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

    render_color(YELLOW, 255);
   // this->score.draw(renderer, 120);
    // dessine tous ce qui doit être affiché
    for (auto i : vm)
        i->draw(renderer);


    for (auto i : enemies){
        // on récupère la couleur de l'ennemi
        render_color(std::move(i->get_color()));
        i->draw(renderer);
    }

    render_color(std::move(map->get_color()));
    map->draw(renderer);

    // for (auto i : collisions){
    //     i.draw(renderer);
    // }

    render_color(std::move(level->get_player_color()));    
    player.draw(renderer);

    render_color(YELLOW, 255);
    
    this->textRenderer.draw(renderer, this->player.get_score(), WIDTH/3, 100, "YELLOW");

    this->textRenderer.draw(renderer, this->player.get_life_point(), 2*WIDTH/3, 100, "LIGHT_BLUE");
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

bool Game::running() { return this->isRunning; }

