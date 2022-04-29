#include "Player.hpp"

// Constructeur
    Player::Player(){}
    // Destructeur
    Player::~Player(){}

    Player::Player(Player&& other)
        : Character(std::move(other))
    {
        this->hall = std::move(other.hall);
        this->color = std::move(other.color);
        this->name = std::string("Player 1");
    }

    Player::Player(const Player& other)
        : Character(other)
    {
        this->hall = other.hall;
        this->color = other.color;
        this->name = std::string("Player 1");
        this->build();
    }

    Player::Player(const int& n_hall, const Tunel& hall, const Color& c){
        this->hall = hall;
        this->color = c;
        this->name = std::string("Player 1");
        this->build();
    }

    Player::Player(const int& n_hall, Tunel&& hall, Color&& c){
        this->hall = hall;
        this->color = c;
        this->name = std::string("Player 1");
        this->build();
    }

    const int Player::get_superzapper() const{
        return this->superzapper;
    }


    const int Player::get_life_point()const  {
        return life_point;
    }

    const int Player::get_score()const {
        return this->score;
    }

    const std::string Player::get_name() const {
        return this->name;
    }

    void Player::set_superzapper(int val){
        this->superzapper = val;
    }

    const bool Player::dec_superzapper(){
        return(--this->superzapper>=0);
    }

    void Player::incr_n_hall(Tunel&& h) {
        this->hall = h;
        this->clean();
        this->build();
    }

    void Player::decr_n_hall(Tunel&& h) {
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

     void Player::set_name(std::string&& name){
         this->name = name;
     }

    void Player::incr_score(int points){
        this->score += points;
    }

    void Player::build(){

        Line big_line { std::move(this->hall.get_big_line())};
        Line small_line { std::move(this->hall.get_small_line())};
        Point p1 { std::move(big_line.get_p0())};
        Point p3 { std::move(big_line.get_p1())};

        Line l1 {std::move(small_line.inLine(0.7)), std::move(big_line.inLine(0.7))};
        Point p2 = std::move(l1.inLine(1.2));
        l1.set_p0( std::move(small_line.inLine(0.6)));
        l1.set_p1( std::move(big_line.inLine(0.6)));
        Point p6 { std::move(l1.inLine(1.1))};
        Point p5 { std::move(big_line.inLine(0.80))};
        Point p7 { std::move(big_line.inLine(0.20))};

        Line l2 {std::move(small_line.inLine(0.25)), std::move(big_line.inLine(0.25))};
        Line l3 {std::move(small_line.inLine(0.75)), std::move(big_line.inLine(0.75))};

        Point p0 { std::move(l2.inLine(0.9))};
        Point p4 { std::move(l3.inLine(0.9))};

        this->lines.push_back(std::move(Line(p0, p1, this->thickness)));
        this->lines.push_back(std::move(Line(p1, p2, this->thickness)));
        this->lines.push_back(std::move(Line(p2, p3, this->thickness)));
        this->lines.push_back(std::move(Line(p3, p4, this->thickness)));
        this->lines.push_back(std::move(Line(p4, p5, this->thickness)));
        this->lines.push_back(std::move(Line(p5, p6, this->thickness)));
        this->lines.push_back(std::move(Line(p6, p7, this->thickness)));
        this->lines.push_back(std::move(Line(p7, p0, this->thickness)));

    }

    void Player::draw(std::shared_ptr<SDL_Renderer> renderer) {
        for (auto i : this->lines)
            i.draw_shadow(renderer);
        for (auto i : this->lines)
            i.draw(renderer);
    }

    void Player::operator=(Player other){
        this->hall = other.hall;
        this->color = other.color;
        this->name = other.name;
        this->build();
    }