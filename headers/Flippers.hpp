#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers(){}

    //constructeur
    Flippers(std::string name, Point center, int w){

        this->name = name;
        this->center = center;
        this->width = w;
        this->height = w/2;

        build();
    }

    //destructeur
    ~Flippers(){}

    void build(){
        //line 1
        Point p1, p2, p3, p4, p5, p6;
        std::array<Line, 6> l;

        p1.set_point(center.get_x() - width/2, center.get_y() - height/2);
        p2.set_point(center.get_x() + width/2, center.get_y() + height/2);
        l[0] = Line(p1, p2);

        p3.set_point(p2.get_x() - width/6, center.get_y());
        l[1] = Line(p2, p3);

        p4.set_point(p2.get_x(), p2.get_y() + 2*height/3);
        l[2] = Line(p3, p4);

        p5.set_point(p1.get_x(), p1.get_y() - 2*height/3);
        l[3] = Line(p4, p5);

        p6.set_point(p1.get_x() + width/6, p3.get_y());
        l[4] = Line(p5, p6);

        l[5] = Line(p6, p1);

        for(auto i : l){
            this->lines.push_back(i);
        }

    }

    void clean(){
        this->lines.clear();
    }

     /**
     * @brief Set the dest object
     * 
     * @param dest 
     */
    void set_dest (Point destination) {
        this->dest = destination;
    }

    /**
     * @brief Rapproche le point de la destination 
     * (+ ou - en fct de la variable "vitesse")
     *  
     * @return vrai si on a atteint l'objectif (= doit être détruit)
     */
    bool get_closer() {

        Line trajectoire(this->center, this->dest);
        Point old_center = this->center;
        this->center = trajectoire.inLine(1.0 / (double) speed);
        this->width = this->width + 1;
        this->height = this->width / 2;
        this->clean();
        this->build();
        
        return intersect(this->bigLine);
    }

    bool intersect(Line l){
        SDL_Rect r;
        r.w = width;
        r.h = height;
        r.x = center.get_x();
        r.y = center.get_y();
        int x1 = l.get_p0().get_x();
        int y1 = l.get_p0().get_y();
        int x2 = l.get_p1().get_x();
        int y2 = l.get_p1().get_y();

        return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

    }

    void draw(SDL_Renderer* renderer){
        for (auto i : lines) {
            i.draw(renderer);
        }
    }

    

private:
};


#endif