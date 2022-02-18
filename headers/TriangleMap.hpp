#ifndef __TRIANGLEMAP_HPP__
#define __TRIANGLEMAP_HPP__

#include "Map.hpp"

class TriangleMap : private Map {

public:

    //constructeur
    TriangleMap(){}

    TriangleMap(int nbHall, int width, int height){

        this->nbHall = nbHall;
        this->width = width/3;
        this->height = 6 * height/8;

        setBigTriangle(width, height);

        setMedians(width);

        this->barycentre = median_1.intersect(median_2);

        setSmallTriangle();
    }

    //destructeur
    ~TriangleMap(){}

    void setBigTriangle(int width, int height){
        // Base du triangle
        bigTriangle[0] = new Point(width/2 - this->width/2, height/2 - this->height/2);
        bigTriangle[1] = new Point(width/2 + this->width/2, height/2 - this->height/2);

        // Point supérieur
        bigTriangle[2] = new Point(width/2, height/2 + this->height/2);
    }

    void setMedians(int width){
        Point* mid_1 = new Point( width/2 - abs( bigTriangle[2]->get_x() - bigTriangle[0]->get_x() ) / 2, bigTriangle[0]->get_y() + abs( bigTriangle[2]->get_y() - bigTriangle[0]->get_y() ) / 2);
        Point* mid_2 = new Point( width/2 + abs( bigTriangle[2]->get_x() - bigTriangle[1]->get_x() ) / 2, bigTriangle[0]->get_y() + abs( bigTriangle[2]->get_y() - bigTriangle[1]->get_y() ) / 2);
        Point* mid_3 = new Point( width/2, bigTriangle[0]->get_y());

        medians[0] = new Line(bigTriangle[0], mid_2);
        medians[1] = new Line(bigTriangle[1], mid_1);
        medians[2] = new Line(bigTriangle[2], mid_3);
    }

    void setSmallTriangle(){
        smallTriangle[0] = 
    }

    void buildMap(){
        int hallPerSide = nbHall / 3;
        int nbLastSide = hallPerSide + nbHall % 3;

        for(int i = 0; i < hallPerSide; i++){
            add_Hall(new Hall());
        }
        for(int i = 0; i < hallPerSide; i++){
            
        }
        for(int i = 0; i < nbLastSide; i++){
            
        }
    }

private:
    double width;
    double height;
    Point* barycentre;
    std::array<Point*, 3> bigTriangle;
    std::array<Point*, 3> smallTriangle;
    std::array<Line*, 3> medians;
};


#endif