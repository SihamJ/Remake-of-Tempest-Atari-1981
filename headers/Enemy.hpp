#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__


#include "Line.hpp"
#include "Tunel.hpp"

class Enemy {

public:

    Enemy();
    Enemy(Color& c);
    Enemy(const Point& center, const Tunel& h, const std::array<Point, 4> &rect);

    ~Enemy();

    Point get_center();
    Tunel get_hall();
    std::vector<Line> get_lines();
    std::array<Point, 4> get_rect();
    Color get_color();
    virtual std::string get_name();
    virtual const int get_scoring()=0;

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer)= 0;

    void set_hall(const Tunel& hall);
    void set_bigLine(const Line& l);
    virtual void build()= 0;

    virtual void set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect)= 0;
    virtual bool get_closer()= 0;

protected:

    Color color;
    // nom de l'ennemi
    std::string name;

    // destination de l'ennemi
    Point dest;
    Point start;

    // + la vitesse est haute + on se rapproche du centre avec get_closer
    int speed = 10;
    
    // couloir auquel appartient l'ennemi
    Tunel hall;

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