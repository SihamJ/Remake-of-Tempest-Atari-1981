#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"


class Player : public Character {

public:

    Player();
    Player(Player&& other);
    Player(const Player& other);
    Player(const int& n_hall, const Tunel& hall, const Color& c);
    Player(const int& n_hall, Tunel&& hall, Color&& c);

    ~Player();

    const int get_life_point()const ;
    const int get_score()const ;
    const std::string get_name() const override;
    const int get_superzapper() const;

    void set_score(int score);
    void set_name(std::string&& name);
    void set_superzapper(int val);

    void incr_n_hall( Tunel&& h);
    void decr_n_hall( Tunel&& h);
    bool decr_life_point();
    void incr_score(int points);
    const bool dec_superzapper();

    void build();
    void draw(std::shared_ptr<SDL_Renderer> renderer) override;

    void operator=(Player other);

protected:

    int life_point = INIT_VIE;
    int score = 0;
    const int thickness = 4;
    int superzapper = 2;
};

#endif