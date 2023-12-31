#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();
    Flippers(const std::string&&  name);
    Flippers(const std::string&&  name, const  Color&& c);
    Flippers(const std::string&& name, const  Point&& center, const  Tunel&& h);
    Flippers(const Flippers &other);
    Flippers(const Flippers &&other);

    ~Flippers();
    std::vector<Line> get_lines(){ return this->lines; }
    const long double get_speed() const ;
    const Tunel get_next_hall() const;
    const double get_current_angle() const;
    const double get_next_angle() const;
    const int get_state() const ;
    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set(Tunel&& h);
    void set_next_hall(Tunel &&h);
    void set_current_angle(double angle);
    void set_next_angle(double angle);
    void set_flipping(bool flipping);

    std::string get_name(){ return "Flippers";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer(long double h) override;
    const bool flip();
    const bool shoot();

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    bool intersect(Line l);    
    const bool flipping() const;

private:
    const int scoring=150;
    const int init_width = 128;
    const int init_height = 49;
    const long double speed = 0.05;
    int width;
    int height;
    int state = 0;
    Line limit_init;
    float random_p;
    float next_angle = 0;
    float current_angle = 0;
    float r;
    const int flip_steps = 10;
    bool isFlipping = false;
    Tunel next_hall;
    Point flip_center;
    bool first = true;
    long double xflip;
    long double yflip;
};


#endif
