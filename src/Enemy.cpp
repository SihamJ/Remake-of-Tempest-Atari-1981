#include "../headers/Enemy.hpp"
   
   
    Enemy::Enemy()
    {
        this->name = std::move(static_cast<std::string>("Enemy"));
    }

    Enemy::Enemy(Color& c) 
    {
        this->color = c;
        this->name = std::move(static_cast<std::string>("Enemy"));
    }

    Enemy::Enemy(const Point& center, const Tunel& h, const std::array<Point, 4> &rect)
        :  center(center), hall(h), rect(rect)
    {
        name = std::move(static_cast<std::string>("Enemy"));
    }
    
    // ~Enemy(){}
    Enemy::~Enemy(){}

    Point Enemy::get_center(){
        return this->center;
    }

    Tunel Enemy::get_hall(){
        return this->hall;
    }


    void Enemy::set_hall(const Tunel& hall){
        this->hall = hall;
    }

    std::string Enemy::get_name(){
        return "Enemy";
    }

    Color Enemy::get_color(){
        return this->color;
    }

    std::array<Point, 4> Enemy::get_rect(){ return this->rect;}

    bool Enemy::get_closer(){ return false; }
    
