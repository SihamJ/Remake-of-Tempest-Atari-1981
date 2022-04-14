#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();

    //constructeur
    Flippers(const char* name);

    Flippers(const char* name, Color c);

    //constructeur
    Flippers(const char* name, const Point center, const Tunel h, const std::array<Point, 4> rect);

    //constructeur par copie
    Flippers(const Flippers &other);

    //destructeur
    ~Flippers();

    void build() override;

    void clean();

    std::vector<Line> get_lines(){return this->lines; }

    void set_dest (const Point destination);
    void set_tunnel(const Tunel h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point center);
    

    std::string get_name(){ return "Flippers";}

    bool get_closer();

    bool intersect(Line l);    

private:
    
};


#endif