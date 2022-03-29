#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__


#include "Line.hpp"

class Enemy {

public:

    Enemy(){}

    Enemy(std::string name, Point center, Point ch, Hall h){
        this->name = name;
        this->center = center;
        this->ch = ch;
        this->hall = h;
    }

    // ~Enemy(){}
    virtual ~Enemy(){}

    Point get_center(){
        return this->center;
    }

    void set_bigLine(Line l){
        this->bigLine = l;
    }

    virtual void draw(SDL_Renderer* renderer){
        for (auto i : lines) {
            i.draw(renderer);
        }
    }

    // virtual void getName();
    // virtual void build();
    // virtual void move();
    // virtual void rotate();
    // virtual void destroy();
    // virtual void resize();
    // virtual void replace();

protected:

    std::vector<Line> lines;
    std::vector<Line> shadows;
    // un rectangle contenant la forme
    std::string name;
    // destination de l'ennemi
    Point dest;
    // + la vitesse est haute + on se rapproche du centre avec get_closer
    int speed = 10;

    // couloir auquel appartient l'ennemi
    Hall hall;
    // centre de gravité. Servira comme position de départ (initialisé au centre de la map)
    Point center;

    Point ch;
    Line bigLine;
    // la taille du rectangle qui encadre l'ennemi
};


#endif