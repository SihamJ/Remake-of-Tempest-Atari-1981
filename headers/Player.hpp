#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"


class Player : public Character {

public:
    // Constructeur
    Player();
    // Destructeur
    ~Player();

    Player(const int& n_hall, const Tunel& hall, const Color& c);

    /**
     * @brief Get the n hall object
     * 
     * @return int 
     */
    int get_n_hall();

    /**
     * @brief incrémente le numéro du hall
     * 
     */
    void incr_n_hall(int nbHall, const Tunel& h);
    /**
     * @brief décremente le numéro du hall
     * 
     */
    void decr_n_hall(int nbHall, const Tunel&h);

    /**
     * @brief decremente les pdv et renvoie vrai si le player est mort
     * renvoie faux quand il reste des pdv
     * 
     * @return true 
     * @return false 
     */
    bool decr_life_point();

    /**
     * @brief Get the life point object
     * 
     * @return int 
     */
    int get_life_point();

    int get_score();
    void incr_score(int points);

    void build() override;



protected:
    // le numéro du hall dans lequel le joueur se trouve
    int n_hall = 0;
    // point de vie
    int life_point = 20;
    int score = 0;

};

#endif