#ifndef __MAP_HALL_HPP__
#define __MAP_HALL_HPP__

#include <vector>
#include <SDL.h>
#include "Hall.hpp"

class Map_Hall {

public:
    // constructeur
    Map_Hall(){}
    // destructeur
    ~Map_Hall(){}

    /**
     * @brief Ajout d'un couloir à la map
     * 
     * @param h 
     */
    void add_Hall (Hall h) {
        hallList.push_back(h);
    }

    /**
     * @brief dessine la map (= dessine tous les couloirs)
     * 
     * @param renderer 
     */
    void draw(SDL_Renderer* renderer) {
        for (auto i : hallList) {
            i.draw(renderer);
        }
    }

private:
    // Liste des couloirs qui forment la map
    std::vector<Hall> hallList;
    
};

#endif