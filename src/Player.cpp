#include "../headers/Player.hpp"

// Constructeur
    Player::Player(){}
    // Destructeur
    Player::~Player(){}

    Player::Player(Player&& other)
        : Character(std::move(other))
    {
        this->n_hall = std::move(other.n_hall);
        this->hall = std::move(other.hall);
        this->color = std::move(other.color);
        this->build();
    }

    Player::Player(const Player& other)
        : Character(other)
    {
        this->n_hall = other.n_hall;
        this->hall = other.hall;
        this->color = other.color;
        this->build();
    }

    Player::Player(const int& n_hall, const Tunel& hall, const Color& c){
        this->n_hall = n_hall;
        this->hall = hall;
        this->color = c;
        this->build();
    }

    void Player::operator=(Player other){
        this->n_hall = other.n_hall;
        this->hall = other.hall;
        this->color = other.color;
        this->build();
    }


    
    void Player::incr_n_hall(int nbHall, const Tunel& h) {
        n_hall = (n_hall + 1) % nbHall;
        this->hall = h;
        this->clean();
        this->build();
    }

    void Player::decr_n_hall(int nbHall, const Tunel& h) {
        n_hall = (n_hall - 1 + nbHall) % nbHall;
        this->hall = h;
        this->clean();
        this->build();
    }

    bool Player::decr_life_point() {
        if ((--life_point) <= 0) {
            return true;
        }
        return false;
    }

    int Player::get_life_point() {
        return life_point;
    }

    int Player::get_score(){
        return this->score;
    }

    void Player::incr_score(int points){
        this->score += points;
    }

    void Player::build(){

        Line big_line = this->hall.get_big_line();
        Line small_line = this->hall.get_small_line();
        Point p1 = big_line.get_p0();
        Point p3 = big_line.get_p1();

        Line l1 {small_line.inLine(0.7), big_line.inLine(0.7)};
        Point p2 = l1.inLine(1.2);
        l1.set_p0(small_line.inLine(0.6));
        l1.set_p1(big_line.inLine(0.6));
        Point p6 = l1.inLine(1.1);
        Point p5 = big_line.inLine(0.80);
        Point p7 = big_line.inLine(0.20);

        Line l2 {small_line.inLine(0.25), big_line.inLine(0.25)};
        Line l3 {small_line.inLine(0.75), big_line.inLine(0.75)};
        Point p0 = l2.inLine(0.9);
        Point p4 = l3.inLine(0.9);

        this->lines.push_back(Line(p0, p1, this->thickness));
        this->lines.push_back(Line(p1, p2, this->thickness));
        this->lines.push_back(Line(p2, p3, this->thickness));
        this->lines.push_back(Line(p3, p4, this->thickness));
        this->lines.push_back(Line(p4, p5, this->thickness));
        this->lines.push_back(Line(p5, p6, this->thickness));
        this->lines.push_back(Line(p6, p7, this->thickness));
        this->lines.push_back(Line(p7, p0, this->thickness));

    }

    void Player::draw(std::shared_ptr<SDL_Renderer> renderer) {
        for (auto i : this->lines)
            i.draw_shadow(renderer);
        for (auto i : this->lines)
            i.draw(renderer);
    }