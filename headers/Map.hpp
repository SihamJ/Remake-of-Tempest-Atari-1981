#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <SDL.h>
#include "Hall.hpp"

class Map {

public:
    // constructeur
    Map(){}

    Map(std::vector<Hall> hallList){
        this->hallList = hallList;
        this->nbHall = hallList.size();
    }
    // destructeur
    ~Map(){}

    std::vector<Hall> getHallList(){
        return hallList;
    }

    int getNbHall(){
        return this->nbHall;
    }

    Point* get_center(){
        return center;
    }

    /**
     * @brief Ajout d'un couloir à la map
     * 
     * @param h le couloir à ajouter
     */
    void add_Hall (Hall h) {
        hallList.push_back(h);
    }

    void delete_hall(){
        
    }

    virtual void buildMap(){};

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

protected:
    // Liste des couloirs qui forment la map
    std::vector<Hall> hallList;
    int nbHall;
    Point* center;
    
};

#endif