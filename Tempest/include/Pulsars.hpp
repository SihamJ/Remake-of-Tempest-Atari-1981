#ifndef __PULSARS_HPP__
#define __PULSARS_HPP__

#include "Enemy.hpp"


class Pulsars : public Enemy {

public:

    Pulsars();
    Pulsars(std::string&&  name);
    Pulsars(std::string&&  name, Color&& c);
    Pulsars(std::string&& name,  Point&& center,  Tunel&& h);
    Pulsars(const Pulsars &other);
    Pulsars(Pulsars &&other);

    ~Pulsars();

    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set(Tunel&& h);
    
    const std::string get_name() const { return "Pulsars";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer(long double h) override;

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    const bool intersect(Line l) const ;    

private:
    const int scoring=200;
    const int init_width = 128;
    const int init_height = 49;
    int width;
    int height;
    const long double speed = 0.01;
};


#endif
