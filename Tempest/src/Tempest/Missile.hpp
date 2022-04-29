#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "Point.hpp"
#include "Line.hpp"
#include "Tunel.hpp"

class Missile {
    public:
        Missile();
        ~Missile();

        //constructeur
        Missile(const Tunel& h);
        Missile(const Tunel&& h);

        int get_width() const;
        int get_height() const;
        int get_x() const;
        int get_y() const;
        Point get_pos() const;
        bool get_closer();
        Tunel get_hall() const;
        bool get_enemy() const;

        void set_enemy();

        bool intersect(Line l) const;

        void draw(std::shared_ptr<SDL_Renderer> renderer);

        

        

    private:

        // couloir auquel appartient l'ennemi
        Tunel hall;

        Point dest;
        Point start;
        Point pos;

        // taille initial de l'image
        const int init_width = 40;
        const int init_height = 40;

        // taille à changer pr agrandir ou rétrécir l'image de l'ennemi
        int width = 40;
        int height = 40;
        int angle = 0;

        // vrai si c'est un missile ennemi
        bool enemy = false;

};



#endif