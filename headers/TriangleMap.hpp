#ifndef __TRIANGLEMAP_HPP__
#define __TRIANGLEMAP_HPP__

#include "Map.hpp"

class TriangleMap : public Map {

public:

    //constructeur
    TriangleMap(){}

    TriangleMap(int nbHall, int width, int height){

        this->nbHall = nbHall;
        this->width = width/3;
        this->height = 6*height/8;

        setBigTriangle(width, height);

        setMedians(width);

        this->barycentre = medians[0]->intersect(medians[1]);

        setSmallTriangle(0.3);
    }

    //destructeur
    ~TriangleMap(){}

    void setBigTriangle(int width, int height){
        // Base du triangle
        bigTriangle[0] = new Point(width/2 - this->width/2, height/2 + this->height/2);
        bigTriangle[1] = new Point(width/2 + this->width/2, height/2 + this->height/2);

        // Point supérieur
        bigTriangle[2] = new Point(width/2, height/2 - this->height/2);
    }

    void setMedians(int width){
        Point* mid_1 = new Point( width/2 - abs(bigTriangle[2]->get_x() - bigTriangle[0]->get_x()) / 2, bigTriangle[2]->get_y() + abs( bigTriangle[0]->get_y() - bigTriangle[2]->get_y()) / 2);
        Point* mid_2 = new Point( width/2 + abs(bigTriangle[2]->get_x() - bigTriangle[1]->get_x() ) / 2, bigTriangle[2]->get_y() + abs( bigTriangle[1]->get_y() - bigTriangle[2]->get_y() ) / 2);
        Point* mid_3 = new Point( width/2, bigTriangle[0]->get_y());

        medians[0] = new Line(bigTriangle[0], mid_2);
        medians[1] = new Line(bigTriangle[1], mid_1);
    //    medians[2] = new Line(bigTriangle[2], mid_3);
    }

    void setSmallTriangle(double ratio){
        smallTriangle[0] = medians[0]->inLine(ratio);
        smallTriangle[1] = medians[1]->inLine(ratio);
        smallTriangle[2] = new Point(bigTriangle[2]->get_x(), bigTriangle[2]->get_y() + bigTriangle[0]->euclideanDistance(*smallTriangle[0]));
    }

    void buildMap(){
        int hallPerSide = nbHall / 3;
        int nbLastSide = hallPerSide + nbHall % 3;
        std::vector<Point*> bigLines;
        std::vector<Point*> smallLines;
        
        bigLines.push_back(new Point(bigTriangle[0]->get_x(), bigTriangle[0]->get_y()));
        smallLines.push_back(new Point(smallTriangle[0]->get_x(), smallTriangle[0]->get_y()));

        for(int i = 1; i < hallPerSide; i++){
            Point* p1 = new Point(bigTriangle[0]->get_x() + ((bigTriangle[1]->get_x() - bigTriangle[0]->get_x())*i) / hallPerSide, bigTriangle[0]->get_y());
            Point* p2 = new Point(smallTriangle[0]->get_x() + ((smallTriangle[1]->get_x() - smallTriangle[0]->get_x())*i) / hallPerSide, smallTriangle[0]->get_y());
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[1]->get_x(), bigTriangle[1]->get_y()));
        smallLines.push_back(new Point(smallTriangle[1]->get_x(), smallTriangle[1]->get_y()));

        for(int i = 1; i < hallPerSide; i++){
            Point* p1 = new Point(bigTriangle[2]->get_x() + ((bigTriangle[2]->get_x() - bigTriangle[1]->get_x()) * i) / hallPerSide, bigTriangle[1]->get_y() + ((bigTriangle[2]->get_y() - bigTriangle[1]->get_y()) * i) / hallPerSide);
            Point* p2 = new Point(smallTriangle[2]->get_x() + ((smallTriangle[2]->get_x() - smallTriangle[1]->get_x()) * i) / hallPerSide, smallTriangle[1]->get_y() + ((smallTriangle[2]->get_y() - smallTriangle[1]->get_y()) * i) / hallPerSide);
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[2]->get_x(), bigTriangle[2]->get_y()));
        smallLines.push_back(new Point(smallTriangle[2]->get_x(), smallTriangle[2]->get_y()));

        for(int i = 1; i < nbLastSide; i++){
            Point* p1 = new Point(bigTriangle[0]->get_x() + ((bigTriangle[2]->get_x() - bigTriangle[0]->get_x()) * i) / hallPerSide, bigTriangle[0]->get_y() + ((bigTriangle[2]->get_y() - bigTriangle[0]->get_y()) * i) / hallPerSide);
            Point* p2 = new Point(smallTriangle[0]->get_x() + ((smallTriangle[2]->get_x() - smallTriangle[0]->get_x()) * i) / hallPerSide, smallTriangle[0]->get_y() + ((smallTriangle[2]->get_y() - smallTriangle[0]->get_y()) * i) / hallPerSide);
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[0]->get_x(), bigTriangle[0]->get_y()));
        smallLines.push_back(new Point(smallTriangle[0]->get_x(), smallTriangle[0]->get_y()));

        // ajout des couloirs
        for(int i = 0; i < nbHall; i++){
            this->add_Hall( Hall(bigLines.at(i), bigLines.at((i+1) % bigLines.size()), smallLines.at(i), smallLines.at((i+1) % smallLines.size())) );
        }

    }

    std::vector<Hall> getHallList(){
        return this->hallList;
    }

private:
    int width;
    int height;
    Point* barycentre;
    std::array<Point*, 3> bigTriangle;
    std::array<Point*, 3> smallTriangle;
    std::array<Line*, 3> medians;
};


#endif