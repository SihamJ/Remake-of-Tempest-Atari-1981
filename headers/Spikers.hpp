#ifndef __SPIKERS_HPP__
#define __SPIKERS_HPP__

#include "Enemy.hpp"
#include <random>

class Spikers : public Enemy {

public:

    Spikers();
    Spikers(std::string&& name);
    Spikers(std::string&& name, Color&& c);
    Spikers(std::string&& name, Point&& center, Tunel&& h);
    Spikers(const Spikers &other);
    Spikers(Spikers &&other);

    ~Spikers();

    const int get_scoring() const  override;

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);

    void set(Tunel&& h);

    const std::string get_name(){ return this->name;}

    bool get_closer() override;

    Line get_line_limit();

    void decrease_random_p();

    bool intersect(Line l);

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;

    void update_line_limit();

private:
    const int scoring=50;
    const long double speed = 0.001;
    // entre 0.25 et 0.75, le point jusqu'au quel le spiker avance
    // 0.25 proche du centre, 0.75 proche de l'exterieur de la map
    float random_p;
    Line limit_init;
    
    /*
    * 0 : vient d'apparaitre, avance vers un point random
    * 1 : à atteint le point, la ligne est tracé, il recule vers le centre
    * 2 : il avance vers le point, avec la ligne déjà tracé
    * 3 : il recule vers le centre après avoir atteint le point random
    */
    int state = 0;

    // taille initial de l'image
    const int init_width = 57;
    const int init_height = 64;
    
};


#endif
