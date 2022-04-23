#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <string>
#include <SDL.h>
#include <iostream>
#include <time.h>       /* time */
#include <memory>
#include <vector>
#include <cmath>

#include "Point.hpp"
#include "Player.hpp"
#include "TriangleMap.hpp"
#include "Enemy.hpp"
#include "Flippers.hpp"
#include "Color.hpp"
#include "Utils.hpp"
#include "Level.hpp"
#include "SDLWrapper.hpp"
#include "Missile.hpp"
#include "Collision.hpp"
#include "TextRenderer.hpp"
#include "Timer.hpp"

class Game {

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int flagsWindow, int flagsRenderer);

    void handle_events();
    void update();
    void render();
    void clean();

    void next_level();

    void render_color(Color&& c);
    void render_color(std::string color);
    void render_color(std::string color, int opacity);


    // checks if the game is still running
    bool running();
    bool transitioning();

private:

    std::unique_ptr<Timer> timer;
    // temps enregistré pr faire des updates toutes les x secondes
    Uint32 clock = 0;
    bool generated = false;
    // temps enregistré pr mettre un nouveau missile à des temps aléatoires
    Uint32 clock_new_p = 0;

    // savoir si le jeu doit continuer de fonctionner
    bool isRunning;
    bool isTransitioning=false;
    // fenêtre
    std::shared_ptr<SDL_Window> window;

    // rendu
    std::shared_ptr<SDL_Renderer> renderer;

    // L'ensemble des points missiles alliés
    // std::vector<Point> vm;

    std::vector<std::shared_ptr<Missile>> vm;

    // Vecteur des ennemies courants
    std::vector<std::shared_ptr<Enemy>> enemies;

    // Le centre de la Map
    Point center;

    // Ensemble des tunnels (Hall) de la Map courante
    std::vector<Tunel> vh;

    // Le player
    Player player;

    // Map courante
    std::shared_ptr<Tube> map;

    // Une partie est définie par plusieurs niveaux. Chaque niveau contient une Map et des ennemies qui le caractèrisent.
    // Le jeu donc progresse d'un niveau à l'autre en mettant à jour l'attribut level
    std::shared_ptr<Level> level;

    std::vector<Collision> collisions;

    TextRenderer textRenderer;
    

};

#endif