#ifndef __SPIKERS_HPP__
#define __SPIKERS_HPP__

#include "Enemy.hpp"
#include <random>
#include <cmath>


class Spikers : public Enemy {

public:

    Spikers();
    Spikers(const std::string&& name);
    Spikers(const std::string&& name,const  Color&& c);
    Spikers(const std::string&& name, const Point&& center, const Tunel&& h);
    Spikers(const Spikers &other);
    Spikers(const Spikers &&other);

    ~Spikers();

    const int get_scoring() const  override;
    const int get_state() const;
    Line get_line_limit() const ;
    const std::string get_name() const{ return this->name;}
    Line get_limit() const ;

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set_state(int state);
    void set(Tunel&& h);

    bool get_closer(long double h) override;
    bool decrease_random_p();
    bool intersect(Line l) const;
    void update_line_limit();

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;

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
    * 2 : il est arrivé au centre, il lance un missile
    * -1 : missile lancé, il reste que la ligne
    */
    int state = 0;

    // taille initial de l'image
    const int init_width = 57;
    const int init_height = 64;
    
};


#endif
