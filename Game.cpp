#include "Game.hpp"
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
    // if (SDL_INIT(SDL_INIT_EVERYTHING) == 0) {
    // }

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

        // créé 100 points aléatoire sur la fenêtre
        for (int i = 0; i<100; i++) {
            Point p;
            p.set_point(rand()%width, rand()%height);
            p.draw(renderer);
            vp.push_back(p);
        }

        // créé le point central
        center.set_point(rand()%width, rand()%height);
        center.draw(renderer);

        // get les coordonnées du point central
        std::array<int, 2> pc = center.get_point();

        // Calcul 8 lignes pr former un octogone
        // largeur des cotés de l'octogone
        int a = 100;
        // rayon calculé par rapport à a
        int r = (a/2)*(1+sqrt(2));
        // calcul des 8 cotés par rapport au point central
        vh[0].set_big_line(-1*a/2+pc[0],-1*r+pc[1],a/2+pc[0],-1*r+pc[1]);
        vh[1].set_big_line(a/2+pc[0],-1*r+pc[1],r+pc[0],-1*a/2+pc[1]);
        vh[2].set_big_line(r+pc[0],-1*a/2+pc[1],r+pc[0],a/2+pc[1]);
        vh[3].set_big_line(r+pc[0],a/2+pc[1],a/2+pc[0],r+pc[1]);
        vh[4].set_big_line(a/2+pc[0],r+pc[1],-1*a/2+pc[0],r+pc[1]);
        vh[5].set_big_line(-1*a/2+pc[0],r+pc[1],-1*r+pc[0],a/2+pc[1]);
        vh[6].set_big_line(-1*r+pc[0],a/2+pc[1],-1*r+pc[0],-1*a/2+pc[1]);
        vh[7].set_big_line(-1*r+pc[0],-1*a/2+pc[1],-1*a/2+pc[0],-1*r+pc[1]);

        // créé les lignes intérieur et dessine ttes les lignes pr l'octogone
        // les small lines servent à rien
        for (int i = 0; i<8; i++) {
            std::array<int, 4> bigL = vh[i].get_big_line();
            vh[i+8].set_big_line(bigL[0], bigL[1], pc[0], pc[1]);
            vh[i].set_small_line(0,0,0,0);
            vh[i+8].set_small_line(0,0,0,0);
            vh[i].draw(renderer);
            vh[i+8].draw(renderer);
        }

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
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

/**
 * @brief On met à jour tous les éléments -> tous les TICK millisecondes
 * 
 */
void Game::update() {
    // Si on a dépassé les TICK millisecondes, on update
    if (SDL_GetTicks() - clock > TICK) {
        // affiche l'horloge
        std::cout << clock << std::endl;
        // màj de clock
        clock = SDL_GetTicks();
        // Rapproche tous les points existants du point central
        for (int i = 0; i<vp.size(); i++) {
            vp[i].get_closer(center);
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

    for (int i = 0; i<vp.size(); i++) {
        vp[i].draw(renderer);
    }
    center.draw(renderer);
    
    for (auto i : vh) {
        i.draw(renderer);
    }
    
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

