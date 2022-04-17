#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__


#include "Line.hpp"
#include "Tunel.hpp"

class Enemy {

public:

    Enemy();

    Enemy(Color& c);

    Enemy(const Point& center, const Tunel& h, const std::array<Point, 4> &rect);

    // ~Enemy(){}
    ~Enemy();

    Point get_center();
    void set_bigLine(const Line& l);

    void set(const Point& center, const Tunel& h, const std::array<Point, 4> &rect);
    void set(Point&& center, Tunel&& h, std::array<Point, 4> &&rect);

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer);

    virtual std::string get_name();

    std::vector<Line> get_lines();

    std::array<Point, 4> get_rect();

    Color get_color();

    virtual void build();
    virtual bool get_closer();
    
    // virtual void move();
    // virtual void rotate();
    // virtual void destroy();
    // virtual void resize();
    // virtual void replace();

protected:

    std::vector<Line> lines;
    std::vector<Line> shadows;
    Color color;

    // nom de l'ennemi
    std::string name;

    // destination de l'ennemi
    Point dest;
    // + la vitesse est haute + on se rapproche du centre avec get_closer
    int speed = 10;
    
    // couloir auquel appartient l'ennemi
    Tunel hall;
    // centre de gravité. Servira comme position de départ (initialisé au centre de la map)
    Point center;

    Line bigLine;
    // la taille du rectangle qui encadre l'ennemi

    std::array<Point, 4> rect;
};


#endif