#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"

class Player : protected Character {

public:
    // Constructeur
    Player(){}
    // Destructeur
    ~Player(){}

    /**
     * @brief Get the n hall object
     * 
     * @return int 
     */
    int get_n_hall() {
        return n_hall;
    }

    /**
     * @brief incrémente le numéro du hall
     * 
     */
    void incr_n_hall() {
        n_hall = (n_hall + 1) % 8;
    }

    /**
     * @brief décremente le numéro du hall
     * 
     */
    void decr_n_hall() {
        n_hall = (n_hall + 7) % 8;
    }

    /**
     * @brief decremente les pdv et renvoie vrai si le player est mort
     * renvoie faux quand il reste des pdv
     * 
     * @return true 
     * @return false 
     */
    bool decr_life_point() {
        if ((--life_point) <= 0) {
            return true;
        }
        return false;
    }

    /**
     * @brief Get the life point object
     * 
     * @return int 
     */
    int get_life_point() {
        return life_point;
    }


protected:
    // le numéro du hall dans lequel le joueur se trouve
    int n_hall = 0;
    // point de vie
    int life_point = 10;
};

#endif