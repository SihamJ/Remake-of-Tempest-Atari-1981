#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"


class Player : public Character {

public:
    // Constructeur
    Player();
    Player(Player&& other);
    Player(const Player& other);
    // Destructeur
    ~Player();

    Player(const int& n_hall, const Tunel& hall, const Color& c);
    void operator=(Player other);

    int get_n_hall();

    void incr_n_hall(int nbHall, const Tunel& h);

    void decr_n_hall(int nbHall, const Tunel&h);


    bool decr_life_point();

    void build();

    int get_life_point();

    int get_score();
    void incr_score(int points);


    void draw(std::shared_ptr<SDL_Renderer> renderer) override;

protected:
    // le numéro du hall dans lequel le joueur se trouve
    int n_hall = 0;
    // point de vie
    int life_point = 20;
    int score = 0;
    const int thickness = 4;
};

#endif