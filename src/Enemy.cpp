#include "../headers/Enemy.hpp"
   
   
    Enemy::Enemy()
    {
        this->name = std::move(static_cast<std::string>("Enemy"));
    }

    Enemy::Enemy(Color&& c) 
    {
        this->color = std::move(c);
        this->name = std::move(static_cast<std::string>("Enemy"));
    }

    Enemy::Enemy(Point&& center, Tunel&& h)
        :  center(std::move(center))
    {
        this->name = std::move(static_cast<std::string>("Enemy"));
        this->hall = std::move(h);
    }
    
    // ~Enemy(){}
    Enemy::~Enemy(){}

    Point Enemy::get_center() const{
        return this->center;
    }


    std::array<Point, 4> Enemy::get_rect() const{ return this->rect;}

    bool Enemy::get_closer(){ return false; }
    
