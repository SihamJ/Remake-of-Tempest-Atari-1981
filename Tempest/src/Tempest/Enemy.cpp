#include "Enemy.hpp"
   
   
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
        this->dest = other.dest;
        this->start = other.start;
    }

    Enemy::Enemy( Enemy&& other)
        : Character(std::move(other))
    {
        this->dest = other.dest;
        this->start = other.start;
    }
    
    // ~Enemy(){}
    Enemy::~Enemy(){}

    Point Enemy::get_center() const{
        return this->center;
    }

    Line Enemy::get_dest() const { return this->dest; }

    Line Enemy::get_start() const { return this->start; }

    bool Enemy::get_closer(long double h){ return false; }
    
    void Enemy::set(Tunel&& h){

        this->hall = h;
        this->start = h.get_small_line();
        this->dest = h.get_big_line();
        
        int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        width = dist/3;
        height = dist/3;

        Point centre_small_line { std::move(hall.get_small_line().inLine(0.5))};
        Point centre_big_line { std::move(hall.get_big_line().inLine(0.5))};

        x = centre_small_line.get_x() - (width/2);
        y = centre_small_line.get_y() - (height/2);

        bool cond1 = false;

        long double segment_a = centre_big_line.get_x() - centre_small_line.get_x();
        long double segment_b = centre_big_line.get_y() - centre_small_line.get_y();
        long double segment_c = sqrt(segment_a * segment_a + segment_b * segment_b);
        
        if (segment_a < 0.) {
            segment_a *= -1.;
            cond1 = true;
        }

        angle = acos(segment_a / segment_c) * (180.0/3.141592653589793238463);
        
        if (cond1) {
            angle *= -1.;
        }

        if (segment_b > 0.) {
            if (angle < 0.) {
                angle -= 90.;
            }
            else {
                angle += 90.;
            }
        }        
    }

SDL_Rect Enemy::get_rect() const {
    return SDL_Rect{static_cast<int>(x), static_cast<int>(y), width, height};
}

const bool Enemy::collides_with(Missile m) const {
    SDL_Rect r_enemy, r_missile, result;
    r_enemy.x = this->x;
    r_enemy.y = this->y;
    r_enemy.h = this->height;
    r_enemy.w = this->width;
    r_missile.x = m.get_x()-m.get_width()/2;
    r_missile.y = m.get_y()+m.get_height()/2;
    r_missile.h = m.get_height()*2;
    r_missile.w = m.get_width()*2;

    std::cout << "enemy: x: " << r_enemy.x << " y:" << r_enemy.y << std::endl;

    std::cout << "missile: x:" << r_missile.x << " y:" << r_missile.y << std::endl;

    bool res = SDL_IntersectRect(&r_enemy, &r_missile, &result);
    if(res) std::cout << "collision ennemi missile" << std::endl;
    return res;
}