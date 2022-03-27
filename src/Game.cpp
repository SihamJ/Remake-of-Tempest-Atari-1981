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
        map = new TriangleMap(5, width, height);
        map->buildMap();
        map->draw(renderer);

         // créé le point central
        center = *(map->get_center());

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
            if (event.key.keysym.sym == SDLK_LEFT) {
                player.decr_n_hall(map->getNbHall());
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                player.incr_n_hall(map->getNbHall());
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            // le couloir où le player se trouve
            Hall h = vh[player.get_n_hall()];
            // big line du couloir
            std::array<int,4> big_line = h.get_big_line();
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
    if (SDL_GetTicks() - clock_new_p > (rand()%20000)) {
        // maj horloge
        clock_new_p = SDL_GetTicks();
        // le point ajouté au centre de l'octogone
        Point p;
        p.set_point(center.get_point()[0], center.get_point()[1]);
        // un couloir aléatoire entre les 8 de l'octogone
        Hall hDest = vh[rand() % vh.size()];
        // big line du couloir choisi
        std::array<int,4> big_line = hDest.get_big_line();
        // le centre de la bigLine
        p.set_dest({(big_line[0]+big_line[2])/2, (big_line[1]+big_line[3])/2});
        // draw
        p.draw(renderer);
        // ajoute le point au vecteur qui répertorie tous les points
        vp.push_back(p);
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
                SDL_Rect r;
                r.w = 1;
                r.h = 1;
                for (int j = 0; j<vp.size(); j++) {
                    r.x = vp[j].get_point()[0];
                    r.y = vp[j].get_point()[1];
                    if (SDL_IntersectRectAndLine(&r, &last_x, &last_y, &vm[i].get_point()[0], &vm[i].get_point()[1]) == SDL_TRUE) {
                        vm.erase(vm.begin()+i);
                        vp.erase(vp.begin()+j);
                        break;
                    }
                }
            }
        }
        // rapprochent missile ennemies
        for (int i = 0; i<vp.size(); i++) {
            if (vp[i].get_closer()) {
                vp.erase(vp.begin()+i);
                if (player.decr_life_point()) {
                    std::cout << "Game over !" << std::endl;
                    isRunning = false;
                }
            }
        }
    }
}

/**
 * @brief On clear + draw tous les éléments
 * 
 */
void Game::render() {
     Line* l = new Line(100, 100, 200 , 200);
        l->draw(renderer);
    // clear la fenêtre en noir
    renderColorBlack();
    if (SDL_RenderClear(renderer) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        isRunning = false;
    }
    // tous les dessins seront en jaune
    renderColorYellow();

    // dessine tous ce qui doit être affiché

    for (auto i : vp)
        i.draw(renderer);
    
    center.draw(renderer);
    
    for (auto i : vm)
        i.draw(renderer);

    map->draw(renderer);

    renderColorLightBlue();
    Point p = Point(200, 100);
    p.draw(renderer);
    //vh[player.get_n_hall()%map->getNbHall()].draw(renderer);
    map->getHallList().at(player.get_n_hall()).draw(renderer);
    // vh[player.get_n_hall()+map->getNbHall()-1].draw(renderer);
    // vh[((player.get_n_hall()+map->getNbHall()+1) % map->getNbHall()) + map->getNbHall()].draw(renderer);
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