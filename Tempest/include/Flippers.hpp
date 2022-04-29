#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();
    Flippers(std::string&& name);
    Flippers(std::string&& name, Color&& c);
    Flippers(std::string&& name,  Point&& center,  Tunel&& h);
    Flippers(const Flippers &other);
    Flippers(Flippers &&other);

    ~Flippers();
    std::vector<Line> get_lines() const { return this->lines; }
    const Tunel get_next_hall() const;
    const double get_current_angle() const;
    const double get_next_angle() const { return this->next_angle; }
    const int get_state() const ;
    const int get_height() { return this->height;}
    const int get_width() { return this->width;}
    const bool will_flip();
    const int get_flip_steps(){ return this->flip_steps;}

    void set_dest (Point&& destination);
    void set_tunnel(Tunel&& h);
    void set_center( Point&& center);
    void set(Tunel&& h);
    void set_next_hall(Tunel &&h);
    void set_current_angle(double angle);
    void set_next_angle(double angle);
    void set_flipping(bool flipping);
    void set_flip_center(Point p);

    std::string get_name(){ return "Flippers";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer(long double h) override;
    bool flip();

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    bool intersect(Line l);    
    const bool flipping() const;
    const bool shoot() ;

private:
    const int scoring=150;
    const int init_width = 128;
    const int init_height = 49;
    int width;
    int height;
    int state = 0;
    Line limit_init;
    float random_p;
    float next_angle = 0;
    float current_angle = 0;
    float r;
    const int flip_steps = 15;
    bool isFlipping = false;
    Tunel next_hall;
    Point flip_center;
    bool done = false;
};


#endif
