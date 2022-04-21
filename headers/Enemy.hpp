#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "Character.hpp"
#include "Line.hpp"
#include "Tunel.hpp"

class Enemy : public Character {

public:

    Enemy();
    Enemy(Color&& c);
    Enemy(Point&& center, Tunel&& h);

    ~Enemy();

    Point get_center() const;
   
    virtual const int get_scoring() const  =0;
    std::array<Point, 4> get_rect() const;

    virtual void set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect)= 0;
    virtual bool get_closer()= 0;

protected:

    // destination de l'ennemi
    Point dest;
    Point start;

    // + la vitesse est haute + on se rapproche du centre avec get_closer
    int speed = 10;

    // centre de gravité. Servira comme position de départ (initialisé au centre de la map)
    Point center;

    // la taille du rectangle qui encadre l'ennemi
    std::array<Point, 4> rect;

    // coordonnee de l'image (top left corner du carré)
    double x, y;

    // taille à changer pr agrandir ou rétrécir l'image de l'ennemi
    int width;
    int height;

    // angle de rotation de l'image
    double angle;

};


#endif