#include "../headers/Enemy.hpp"
   
   
    Enemy::Enemy()
    {
        this->name = std::move(static_cast<std::string>("Enemy"));
    }

    Enemy::Enemy(Color& c) 
        : color(c)
    {
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

    void Enemy::set_bigLine(const Line& l){
        this->bigLine = l;
    }

    void Enemy::set(const Point& center, const Tunel& h, const std::array<Point, 4> &rect){
        this->center = center;
        this->hall = h;
        this->rect = rect;

        int dist = hall.get_small_line().get_p0().euclideanDistance(hall.get_small_line().get_p1());
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

    void Enemy::set(Point&& center, Tunel&& h, std::array<Point, 4> &&rect){
        std::cout << "moved values for enemy" << std::endl;
        this->center = center;
        this->hall = h;
        this->rect = rect;

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

    void Enemy::draw(std::shared_ptr<SDL_Renderer> renderer){
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

    bool Enemy::get_closer(){ return false; }
    
    // virtual void move();
    // virtual void rotate();
    // virtual void destroy();
    // virtual void resize();
    // virtual void replace();
