#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "Character.hpp"
#include "Line.hpp"
#include "Tunel.hpp"
#include <cmath>

class Enemy : public Character {

public:

    Enemy();
    Enemy(Color&& c);
    Enemy(Point&& center, Tunel&& h);
    Enemy(const Enemy& other);
    Enemy( Enemy&& other);

    ~Enemy();

    Point get_center() const;
   
    virtual const int get_scoring() const  =0;

    virtual void set(Tunel&& h);

    virtual bool get_closer(long double h);

    Line get_dest();
    Line get_start();
    SDL_Rect get_rect();

protected:

    // + la vitesse est haute + on se rapproche du centre avec get_closer
     //0.000000000000001;//
     Line start;
     Line dest;

    // centre de gravité. Servira comme position de départ (initialisé au centre de la map)
    Point center;

    // coordonnee de l'image (top left corner du carré)
    long double x, y;

    // taille à changer pr agrandir ou rétrécir l'image de l'ennemi
    int width;
    int height;

    // angle de rotation de l'image
    long double angle = 0.;

};


#endif