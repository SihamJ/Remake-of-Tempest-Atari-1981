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

    Enemy::Enemy(const Enemy& other)
        : Character(other)
    {
        
    }

    Enemy::Enemy( Enemy&& other)
        : Character(std::move(other))
    {
        
    }
    
    // ~Enemy(){}
    Enemy::~Enemy(){}

    Point Enemy::get_center() const{
        return this->center;
    }


    std::array<Point, 4> Enemy::get_rect() const{ return this->rect;}

    bool Enemy::get_closer(){ return false; }
    
    void Enemy::set(Tunel&& h){

        this->hall = h;

        Line small_line = this->hall.get_small_line();
        Line big_line = this->hall.get_big_line();
       
        double r1 = 0.2;
        Point p2 = Line(small_line.get_p1(), big_line.get_p1()).inLine(r1);

        double r2 = r1 * small_line.get_p1().euclideanDistance(big_line.get_p1()) / small_line.get_p0().euclideanDistance(big_line.get_p0()) ;
        Point p3 = Line(small_line.get_p0(), big_line.get_p0()).inLine(r2);
        std::array<Point, 4> rect{small_line.get_p0(), small_line.get_p1(), p2, p3};
        
        this->center = Point(Line(rect.at(0), rect.at(2)).intersect(Line(rect.at(1), rect.at(3))));
        
        this->rect = rect;
        this->start = small_line.inLine(0.5);
        this->pos = start;
        this->dest = big_line.inLine(0.5);        
    }