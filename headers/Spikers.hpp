#ifndef __SPIKERS_HPP__
#define __SPIKERS_HPP__

#include "Enemy.hpp"

class Spikers : public Enemy {

public:

    //constructeur
    Spikers();

    //constructeur
    Spikers(std::string name);

    //constructeur
    Spikers(std::string name, Color& c);

    //constructeur
    Spikers(std::string name, const Point& center, const Tunel& h, const std::array<Point, 4> &rect);

    //constructeur par copie
    Spikers(const Spikers &other);


    //destructeur
    ~Spikers();

    void build() override;

    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    

    std::string get_name(){ return "Spikers";}

    bool get_closer();

    bool intersect(Line l);

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;

private:
    const int scoring=50;
    
};


#endif