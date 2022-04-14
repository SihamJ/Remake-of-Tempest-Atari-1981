#include "../headers/Enemy.hpp"
   
   
    Enemy::Enemy()
    {
        this->name = static_cast<std::string>("Enemy");
    }

    Enemy::Enemy(Color c) 
        : color(c)
    {
        this->name = static_cast<std::string>("Enemy");
    }

    Enemy::Enemy(const Point center, const Tunel h, const std::array<Point, 4> rect)
        :  center(center), hall(h), rect(rect)
    {
        name = static_cast<std::string>("Enemy");
    }

    Enemy::Enemy(const Enemy& other)
        : name(other.name), center(other.center), hall(other.hall), rect(other.rect)
    {

    }

    // ~Enemy(){}
    Enemy::~Enemy(){}

    Point Enemy::get_center(){
        return this->center;
    }

    void Enemy::set_bigLine(const Line l){
        this->bigLine = l;
    }

    void Enemy::set(Point center, const Tunel h, const std::array<Point, 4> rect){
        this->center = center;
        this->hall = h;
        this->rect = rect;
    }

    void Enemy::draw(SDL_Renderer* renderer){
        for (auto i : lines) {
            i.draw(renderer);
        }
    }

    std::string Enemy::get_name(){
        return "Enemy";
    }

    Color Enemy::get_color(){
        return this->color;
    }

    std::vector<Line> Enemy::get_lines(){ return this->lines;}

    std::array<Point, 4> Enemy::get_rect(){ return this->rect;}

    void Enemy::build(){ 
        std::cout<< "base build" <<std::endl;
    }

    bool Enemy::get_closer(){ return false;};
    
    // virtual void move();
    // virtual void rotate();
    // virtual void destroy();
    // virtual void resize();
    // virtual void replace();
