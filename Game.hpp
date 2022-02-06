#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <string>
#include "SDL.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Point.hpp"
#include <vector>
#include "Hall.hpp"
#include "Map_Hall.hpp"

#define TICK 100


class Game {

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, int flagsWindow, int flagsRenderer);

    void handleEvents();
    void update();
    void render();
    void clean();
    void renderColorBlack();
    void renderColorYellow();

    /**
     * @brief getter : the game is running ?
     * 
     * @return true 
     * @return false 
     */
    bool running() { return isRunning; }

private:
    // temps enregistré pr faire des updates toutes les x secondes
    Uint32 clock = 0;
    // temps enregistré pr mettre un nouveau missile à des temps aléatoires
    Uint32 clock_new_p = 0;
    // savoir si le jeu doit continuer de fonctionner
    bool isRunning;
    // fenêtre
    SDL_Window *window;
    // rendu
    SDL_Renderer *renderer;
    // L'ensemble des points
    std::vector<Point> vp;
    // Le centre où les points se rassemblent
    Point center;
    // L'ensemble des traits pr former l'octogone
    std::array<Hall, 16> vh;

};

#endif