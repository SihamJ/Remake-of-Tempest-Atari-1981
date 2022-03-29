#include "../headers/Game.hpp"
#include <cmath>

/**
 * @brief Construct a new Game:: Game object
 * 
 */
Game::Game() {

}

/**
 * @brief Destroy the Game:: Game object
 * 
 */
Game::~Game() {

}

/**
 * @brief Initialise le jeu
 * 
 * @param title titre de la fenêtre
 * @param xpos la position en abscisse de la fenêtre
 * @param ypos la position en ordonnée de la fenêtre
 * @param width la largeur de la fenêtre
 * @param height la hauteur de la fenêtre
 */
void Game::init(const char *title, int xpos, int ypos, int width, int height, int flagsWindow, int flagsRenderer) {

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		std::cout << "SDL Init" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flagsWindow);
        if (window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, flagsRenderer);
        if (renderer) {
            std::cout << "Renderer created" << std::endl;
        }

        // pr utiliser rand avec des valeurs randoms
        srand (time(NULL));

        // construction de la map
        map = std::make_unique<TriangleMap>(15, width, height);
        map->buildMap();
        map->draw(renderer);

         // récupère le point central de la Map
        center.set_point(map->get_center().get_x(), map->get_center().get_y());

        vh = map->getHallList();
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
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_f) {
                player.decr_n_hall(map->getNbHall());
            }
            if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_j) {
                player.incr_n_hall(map->getNbHall());
            }
            if (event.key.keysym.sym == SDLK_SPACE){
                // le couloir où le player se trouve
                Hall h = vh[player.get_n_hall()];
                // big line du couloir
                std::array<int,4> big_line = h.get_big_line().get_coord();
                // Le missile
                Point missile;
                missile.set_point((big_line[0]+big_line[2])/2,(big_line[1]+big_line[3])/2);
                // le centre de la bigLine
                missile.set_dest(center.get_point());
                // draw
                missile.draw(renderer);
                // ajoute le point au vecteur qui répertorie tous les missiles
                vm.push_back(missile);
                break;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            // // le couloir où le player se trouve
            // Hall h = vh[player.get_n_hall()];
            // // big line du couloir
            // std::array<int,4> big_line = h.get_big_line();
            // // Le missile
            // Point missile;
            // missile.set_point((big_line[0]+big_line[2])/2,(big_line[1]+big_line[3])/2);
            // // le centre de la bigLine
            // missile.set_dest(center.get_point());
            // // draw
            // missile.draw(renderer);
            // // ajoute le point au vecteur qui répertorie tous les missiles
            // vm.push_back(missile);
            // break;
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
    if (SDL_GetTicks() - clock_new_p > (rand()%200000)) {
        // maj horloge
        clock_new_p = SDL_GetTicks();

        // un couloir aléatoire entre les 8 de l'octogone
        Hall hDest = vh[rand() % vh.size()];
        Line small_line = hDest.get_small_line();
        Line big_line = hDest.get_big_line();
        double r1 = 0.2;
        
        Point p2 = Line(small_line.get_p1(), big_line.get_p1()).inLine(r1);

        double r2 = r1 * small_line.get_p1().euclideanDistance(big_line.get_p1()) / small_line.get_p0().euclideanDistance(big_line.get_p0()) ;

        Point p3 = Line(small_line.get_p0(), big_line.get_p0()).inLine(r2);

        std::array<Point, 4> rect{small_line.get_p0(), small_line.get_p1(), p2, p3};

        Point c = Point(Line(rect.at(0), rect.at(2)).intersect(Line(rect.at(1), rect.at(3))));
        
        Flippers f = Flippers("flippers", c, hDest, rect);
        
        enemies.push_back(f);
    }
    // Si on a dépassé les TICK millisecondes, on update
    if (SDL_GetTicks() - clock > TICK) {
        // affiche l'horloge
        // std::cout << clock << std::endl;
        // vérifier qu'on delete les points
        // std::cout << vp.size() << std::endl;
        // màj de clock
        clock = SDL_GetTicks();
        // Rapproche tous les missiles de leur destination
        // détruit le missile si il a atteint sa cible
        for (int i = 0; i<vm.size(); i++) {
            if (vm[i].get_closer()) {
                vm.erase(vm.begin()+i);
            }
            else {
                // test si y a collision entre missiles alliés et ennemies
                int last_x = vm[i].get_point()[0];
                int last_y = vm[i].get_point()[1];
               
                for (int j = 0; j<enemies.size(); j++) {
                    SDL_Rect r;
                    r.w = ((Flippers) enemies[j]).get_rect().at(0).euclideanDistance(enemies[j].get_rect().at(1));
                    r.h = ((Flippers) enemies[j]).get_rect().at(1).euclideanDistance(enemies[j].get_rect().at(2));
                    r.x = enemies[j].get_center().get_x();
                    r.y = enemies[j].get_center().get_y();
                    if (SDL_IntersectRectAndLine(&r, &last_x, &last_y, &last_x, &last_y) == SDL_TRUE) {
                        vm.erase(vm.begin()+i);
                        enemies.erase(enemies.begin()+j);
                        break;
                    }
                }
            }
        }

         for (int i = 0; i<enemies.size(); i++) {
            if (enemies[i].get_closer()) {
                enemies.erase(enemies.begin()+i);
                if (player.decr_life_point()) {
                    std::cout << "Game over !" << std::endl;
                    isRunning = false;
                }
                std::cout << player.get_life_point() << std::endl;
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
    renderColorBlack();
    if (SDL_RenderClear(renderer) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }
    // tous les dessins seront en jaune
    renderColorYellow();

    // dessine tous ce qui doit être affiché
    
    center.draw(renderer);
    
    for (auto i : vm)
        i.draw(renderer);

    renderColorRed();

    for (auto i : enemies)
        i.draw(renderer);

    renderColorYellow();

    map->draw(renderer);

   
    renderColorLightBlue();
    
    
    map->getHallList().at(player.get_n_hall()).draw(renderer);

    renderColorYellow();
    
    
    // màj du rendu
    SDL_RenderPresent(renderer);
}

/**
 * @brief Clean tout quand l'utilisateur a décidé de quitter le jeu
 * 
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

/**
 * @brief Change la couleur pr dessiner en noir
 * 
 */
void Game::renderColorBlack () {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

/**
 * @brief Change la couleur pr dessiner en jaune
 * 
 */
void Game::renderColorYellow () {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
}

/**
 * @brief Change la couleur pr dessiner en blue clair
 * 
 */
void Game::renderColorLightBlue() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 1);
}

/**
 * @brief Change la couleur pr dessiner en rouge
 * 
 */
void Game::renderColorRed () {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}