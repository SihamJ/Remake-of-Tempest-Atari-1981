#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "Character.hpp"
#include "Line.hpp"
#include "Tunel.hpp"
#include "Missile.hpp"
#include <cmath>
#include <random>



class Enemy : public Character {

public:

    Enemy();
    Enemy(const Color&& c);
    Enemy(const Point&& center, const Tunel&& h);
    
    Enemy(const Enemy& other);
    Enemy( const Enemy&& other);

    ~Enemy();

    Point get_center() const;
   
    virtual const int get_scoring() const  = 0;

    /**
     * @brief Déplacement de l'ennemi dans sa trajectoire
     * 
     * @return vrai si l'ennemi a atteint sa cible (souvent c'est la périphérie)
     */
    virtual bool get_closer(long double h);
    Line get_dest() const;
    Line get_start() const;
    SDL_Rect get_rect() const;
    int get_width(){ return this->width;}
    int get_height(){ return this->height;}

    virtual void set(Tunel&& h);
    void set_center( Point&& center);
    void set_width(int width);
    void set_height(int height);
    const bool collides_with(Missile m) const;

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

    // random number generator
    std::random_device rd;

};


#endif