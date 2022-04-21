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

    bool Enemy::get_closer(){ return false; }
    
    void Enemy::set(Tunel&& h){

        this->hall = h;

        int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        width = dist/3;
        height = dist/3;

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - (width/2);
        y = centre_small_line.get_y() - (height/2);

        bool cond1 = false;

        double segment_a = centre_big_line.get_x() - centre_small_line.get_x();
        double segment_b = centre_big_line.get_y() - centre_small_line.get_y();
        double segment_c = sqrt(segment_a * segment_a + segment_b * segment_b);
        
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