#include <Game.hpp>

// width and height of our window
int WIDTH = 1400;
int HEIGHT = 800;
extern int SOUND;
extern int SOUND2;
extern int MENU;
extern int GAMEOVER;
extern int SHOOT;
extern int ENEMYSHOOT;
extern int SUPERZAPPER;
extern int FLIPPERATTACK;
extern int PLAYERTOUCHE;
extern int SCORE;
extern int LEVEL;
extern int PAUSE;
extern int SOUND2;


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

    if (init_sdl(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        // si problème, le jeu doit s'arrêter
        isRunning = false;
        return;
    }

    window = create_window(title, xpos, ypos, flagsWindow);
    renderer = create_renderer(window, -1, flagsRenderer);
    int w,h;
    
    get_window_size(window, &w, &h);
    WIDTH = w;
    HEIGHT = h;

    // int nbth = std::thread::hardware_concurrency();
    // this->th.reserve(nbth);


    this->timer = std::make_shared<Timer>();
    
    // clock 1 game update
    this->timer->add_clock();
    // clock 2 pour enemies
    this->timer->add_clock();
    // clock 3 pour passer au niveau suivant
    this->timer->add_clock();
    // clock 4 pour animation courante
    this->timer->add_clock();
    // clock 5 pour tir par seconde
    this->timer->add_clock();

    this->level = std::make_shared<Level>();
    this->level->next_level();
    this->player.set_score(this->level->get_level_score());
    this->map = level->get_map();

    // construction de la map
    map->build_map();
    this->player = Player(0, std::move(map->get_hall(0)), std::move(this->level->get_player_color()));
    // récupère le point central de la Map
    center.set_point( map->get_center().get_x(), map->get_center().get_y());
    
    vh = map->get_hall_list();
    isRunning = true;
    
}

/**
 * @brief Gère les évènements de l'utilisateur (click souris/tape au clavier)
 * 
 */
void Game::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch((&event)->type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_SPACE){
                // MAX 10 TIR PAR SECONDE
                if(this->timer->get_clock(clock_list::shots) > 500){
                    this->timer->reset_clock(clock_list::shots);
                    nb_shots = 0;
                }
                if(nb_shots < 10){
                    SHOOT = 1;
                    nb_shots ++;                    
                    // le couloir où le player se trouve
                    Tunel h = this->map->get_hall(player.get_n_hall());

                    std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(h));
                    // ajoute le point au vecteur qui répertorie tous les missiles
                    vm.push_back(std::move(m));
                }     
                break;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                MENU = 1;
                setPause(true);
                // On met en pause les timer de passage au niveau suivant et de transition courante s'il y en une
                this->timer->pause_clock(clock_list::level);
                this->timer->pause_clock(clock_list::current_transition);
                break;
            }
            if(event.key.keysym.sym == SDLK_RIGHT)
                player.decr_n_hall ( std::move (map->get_hall (player.get_n_hall () - 1)) );

            if(event.key.keysym.sym == SDLK_LEFT)
                player.incr_n_hall ( std::move (map->get_hall (player.get_n_hall () + 1)) );

            if(event.key.keysym.sym == SDLK_z){
                if( !this->superzapping && player.dec_superzapper()){
                    SUPERZAPPER = 1;
                    this->superzapper(player.get_superzapper()==0 ? false : true);
                }
            }
            if(event.key.keysym.sym == SDLK_m){
                SOUND2 =  SOUND2 == 0 ? 1 : 0;
                break;
            }
            if(event.key.keysym.sym == SDLK_q){
                isRunning = false;
                break;
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
        LEVEL = 1;
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
           // generated = true;
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
        timer->reset_clock(clock_list::update);

        for (auto e : enemies) {

            std::shared_ptr<Spikers> enemy_spiker = std::dynamic_pointer_cast<Spikers>(e);
            std::shared_ptr<Flippers> enemy_flipper = std::dynamic_pointer_cast<Flippers>(e);

            if (enemy_spiker == nullptr && enemy_flipper == nullptr)
                continue;

            if (enemy_spiker != nullptr && enemy_spiker->get_state() == 2) {
                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(enemy_spiker->get_hall()));
                m->set_enemy();
                vm.push_back(std::move(m));
                ENEMYSHOOT=1;
                enemy_spiker->set_state(-1);
            }
            else if(enemy_flipper != nullptr && enemy_flipper->get_state() == 0 && enemy_flipper->shoot()){
                std::shared_ptr<Missile> m = std::make_shared<Missile>(std::move(enemy_flipper->get_hall()));
                m->set_enemy();
                m->set_pos(enemy_flipper->get_center());
                vm.push_back(std::move(m));
                ENEMYSHOOT=1;
            }
            
        }

        // collisions.clear();

        //timer->reset_clock(clock_list::update);
        // Rapproche tous les missiles de leur destination
        // détruit le missile si il a atteint sa cible
        
        for (auto it = vm.begin(); it != vm.end(); it++) {

            bool cond = false;
            if ((*it)->get_closer()) {
                if ((*it)->get_enemy() && this->player.get_hall() == (*it)->get_hall()) {
                    PLAYERTOUCHE = 1;
                    if(this->player.decr_life_point()){
                        GAMEOVER = 1;
                        this->setGameOver(true);
                        this->setStart(false);
                        this->game_over_msg = std::string("YOU LOST ALL YOUR LIFE POINTS");
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
                    if(enemy_spiker == nullptr && (*e)->collides_with(*(*it))) {
                        SCORE = 1;
                        this->player.incr_score((*e)->get_scoring());
                        vm.erase(it--);
                        enemies.erase(e--);
                        ENEMYSHOOT=1; // TO DO change to collision sound
                        break;
                    }

                    // si on tire sur la ligne d'un spiker en état -1, on diminue la ligne
                    if(enemy_spiker != nullptr) {
                        // if (enemy_spiker->get_state() == -1) {
                            // detruit le missile si il atteint la ligne verte du spiker + diminue la ligne verte du spiker
                            double dist1 = (*it)->get_pos().euclideanDistance((*e)->get_hall().get_big_line().inLine(0.5));
                            double dist2 = (*e)->get_hall().get_big_line().inLine(0.5).euclideanDistance(enemy_spiker->get_line_limit().inLine(0.5));

                            if (dist1 > dist2) {

                                vm.erase(it--);
                                if (!enemy_spiker->decrease_random_p())
                                    enemy_spiker->update_line_limit();
                                break;
                            }
                        // }
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
            std::shared_ptr<Tankers> t = std::dynamic_pointer_cast<Tankers>(*i);
            // std::shared_ptr<Pulsars> p = std::dynamic_pointer_cast<Pulsars>(*i);
            // std::shared_ptr<Fuseballs> fu = std::dynamic_pointer_cast<Fuseballs>(*i);
            std::shared_ptr<PulsarTankers> pt = std::dynamic_pointer_cast<PulsarTankers>(*i);
            std::shared_ptr<FuseballTankers> ft = std::dynamic_pointer_cast<FuseballTankers>(*i);
            
            // si c'est un flipper, on check son état (entrain de flipper, va flipper, ou ne rien faire)                
            if( f!= NULL && f->get_state() == 1 && !f->flipping()){
                std::mt19937 gen(this->rd());
                std::uniform_int_distribution<int> rand (0, 2);
                int nbhall = rand(gen) == 0 ? 1: -1;
                f->set_next_hall(this->map->get_hall(f->get_hall().get_n_hall() + nbhall));
                f->set_next_angle(f->get_hall().get_angle(f->get_next_hall()));
                //f->set_flipping(true);
            }

            // si c'est un spiker à l'état 1 (marche arrière), les paramètres d'homothétie seront différents
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
                if((*i)->get_n_hall() == player.get_n_hall()) {
                    if (f != nullptr) {
                        GAMEOVER = 1;
                        this->setGameOver(true);
                        this->setStart(false);
                        game_over_msg = std::string("YOU WERE KILLED BY THE FLIPPER");
                        return;
                    }
                    
                    if (player.decr_life_point()) {
                        GAMEOVER = 1;
                        this->setGameOver(true);
                        this->setStart(false);
                        game_over_msg = std::string("You Died");
                        return;
                    }

                }
                else if(t != nullptr || pt != nullptr || ft != nullptr){
                    std::shared_ptr<Enemy> e1;// = std::make_shared<Flippers>("flipper", std::move(this->level->get_enemies().at(enemies_list::flippers)));
                    std::shared_ptr<Enemy> e2;// = std::make_shared<Flippers>("flipper", std::move(this->level->get_enemies().at(enemies_list::flippers)));

                    if (t != nullptr) {
                        e1 = std::make_shared<Flippers>("flipper", std::move(this->level->get_enemies().at(enemies_list::flippers)));
                        e2 = std::make_shared<Flippers>("flipper", std::move(this->level->get_enemies().at(enemies_list::flippers)));
                    }
                    else if (pt != nullptr) {
                        e1 = std::make_shared<Pulsars>("pulsar", std::move(this->level->get_enemies().at(enemies_list::pulsars)));
                        e2 = std::make_shared<Pulsars>("pulsar", std::move(this->level->get_enemies().at(enemies_list::pulsars)));
                    }
                    else if (ft != nullptr) {
                        e1 = std::make_shared<Fuseballs>("fuseball", std::move(this->level->get_enemies().at(enemies_list::fuseballs)));
                        e2 = std::make_shared<Fuseballs>("fuseball", std::move(this->level->get_enemies().at(enemies_list::fuseballs)));
                    }
                    
                    e1->set(std::move(this->map->get_hall((*i)->get_n_hall()-1))); 
                    e2->set(std::move((*i)->get_hall()));  
                    
                    Point c1 { Line(e1->get_hall().get_small_line().inLine(0.5), e1->get_hall().get_big_line().inLine(0.5)).inLine(0.9) };
                    Point c2 { Line(e2->get_hall().get_small_line().inLine(0.5), e2->get_hall().get_big_line().inLine(0.5)).inLine(0.9) };

                    e1->set_center(std::move(c1));
                    e2->set_center(std::move(c2));
                    e1->set_width(e1->get_hall().get_big_line().length() * 0.8);
                    e1->set_height(e1->get_width() / 2);

                    e2->set_width(e2->get_hall().get_big_line().length() * 0.8);
                    e2->set_height(e2->get_width() / 2);
                    
                    enemies.erase(i--);
                    enemies.push_back(std::move(e1)); 
                    enemies.push_back(std::move(e2));
                    
                    break;
                }
                
                // else if(f == nullptr )
                //     enemies.erase(i--);
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
        if(this->level->get_map_color().get_name() == "BLACK")
            render_color(renderer, Color("WHITE",WHITE));
        else
            render_color(renderer, std::move(this->level->get_map_color()));
        TextRenderer::draw_text(renderer,  std::move(std::string("LEVEL ") + std::to_string(this->level->get_current_level())), WIDTH/2, HEIGHT/4, 3, 2, true);
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

    render_color(renderer, this->level->get_score_color());
    TextRenderer::draw_text(renderer,  std::to_string(this->player.get_score()), 1*WIDTH/3, 50, 1, 2, true);

    // Player Name
    TextRenderer::draw_text(renderer,  this->player.get_name(), WIDTH/2 , 50, 1, 2, true);

    TextRenderer::draw_life(renderer, this->player.get_life_point(), WIDTH/3, 70, this->player.get_color().get_name());

    render_color(renderer, this->map->get_color());
    TextRenderer::draw_text(renderer, std::to_string(this->level->get_current_level()), WIDTH/2, 110, 0.8, 2, true);
    
    if(this->superzapping){
        render_color(renderer, this->level->get_superzapper());
        TextRenderer::draw_text(renderer, "SUPERZAPPER!", WIDTH/2, HEIGHT/2, 2, 4, true);
    }
    
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

void Game::set_level(int level) {
    this->level->set_current_level(level-1);
    next_level();
    this->player.set_score(this->level->get_level_score());
}

void Game::join_threads(){
    for(auto t = this->th.begin(); t != this->th.end(); t++){
        (*t).join();
    }
}




bool Game::running() { return this->isRunning; }
bool Game::transitioning() { return this->isTransitioning; }
bool Game::getPause() { return this->pause; }
void Game::setPause(bool pause) { this->pause = pause; }
void Game::setGameOver(bool go) { this->game_over = go; }
bool Game::getGameOver() { return this->game_over; }
bool Game::getStart() { return this->start; }
void Game::setStart(bool start) { this->start = start; }
std::shared_ptr<SDL_Renderer> Game::getRenderer() { return this->renderer; }
void Game::setIsRunning(bool isRunning) { this->isRunning = isRunning; }
std::shared_ptr<Timer> Game::getTimer() { return this->timer; }
std::shared_ptr<Player> Game::getPlayer() { return std::make_shared<Player>(this->player); }
std::shared_ptr<Level> Game::getLevel() { return this->level; }
std::shared_ptr<Tube> Game::getMap() { return this->map; }
std::string Game::get_msg_game_over() { return this->game_over_msg; }