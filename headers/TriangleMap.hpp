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
        this->height = 3*height/5;

        setBigTriangle(width, height);

        // On calcule de 2 -lignes- médianes du triangles
        setMedians(width);

        // On determine le barycentre (intersection de deux médianes)
        // il servira par la suite comme point central pour les missiles ennemis
        this->center = medians[0]->intersect(medians[1]);

        // On peut maintenant définir le triangle intérieur
        setSmallTriangle(0.6);
    }

    //destructeur
    ~TriangleMap(){}

    // coordonnées du triangle extérieur
    void setBigTriangle(int width, int height){
        // Base du triangle
        bigTriangle[0] = new Point(width/2 - this->width/2, height/2 + this->height/2);
        bigTriangle[1] = new Point(width/2 + this->width/2, height/2 + this->height/2);

        // Point supérieur
        bigTriangle[2] = new Point(width/2, height/2 - this->height/2);
    }

    // médianes du triangle
    void setMedians(int width){
        Point* mid_1 = new Point( width/2 - abs(bigTriangle[2]->get_x() - bigTriangle[0]->get_x()) / 2, bigTriangle[2]->get_y() + abs( bigTriangle[0]->get_y() - bigTriangle[2]->get_y()) / 2);
        Point* mid_2 = new Point( width/2 + abs(bigTriangle[2]->get_x() - bigTriangle[1]->get_x() ) / 2, bigTriangle[2]->get_y() + abs( bigTriangle[1]->get_y() - bigTriangle[2]->get_y() ) / 2);
        Point* mid_3 = new Point( width/2, bigTriangle[0]->get_y());

        medians[0] = new Line(bigTriangle[0], mid_2);
        medians[1] = new Line(bigTriangle[1], mid_1);
    }

    // calcul des coordonnées du triangle intérieur
    void setSmallTriangle(double ratio){
        smallTriangle[0] = medians[0]->inLine(ratio);
        smallTriangle[1] = medians[1]->inLine(ratio);
        smallTriangle[2] = new Point(bigTriangle[2]->get_x(), bigTriangle[2]->get_y() + abs(bigTriangle[0]->get_y() - bigTriangle[2]->get_y())*ratio);
    }

    // Constructions des couloirs
    void buildMap(){
        int hallPerSide = nbHall / 3;
        int nbLastSide = hallPerSide + nbHall % 3;
        std::vector<Point*> bigLines;
        std::vector<Point*> smallLines;

        std::array<Line, 3> linesB;
        std::array<Line, 3> linesS;

        for(int i = 0; i < 3; i++){
            linesB[i] = Line(bigTriangle[i], bigTriangle[(i+1)%3]);
            linesS[i] = Line(smallTriangle[i], smallTriangle[(i+1)%3]);
        }
        
        bigLines.push_back(new Point(bigTriangle[0]->get_x(), bigTriangle[0]->get_y()));
        smallLines.push_back(new Point(smallTriangle[0]->get_x(), smallTriangle[0]->get_y()));

        for(int i = 1; i < hallPerSide; i++){
            Point* p1 = linesB[0].inLine((double)i/(double)hallPerSide);
            Point* p2 = linesS[0].inLine((double)i/(double)hallPerSide);
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[1]->get_x(), bigTriangle[1]->get_y()));
        smallLines.push_back(new Point(smallTriangle[1]->get_x(), smallTriangle[1]->get_y()));

        for(int i = 1; i < hallPerSide; i++){
            Point* p1 = linesB[1].inLine( (double)i/(double)hallPerSide);
            Point* p2 = linesS[1].inLine((double)i/(double)hallPerSide);
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[2]->get_x(), bigTriangle[2]->get_y()));
        smallLines.push_back(new Point(smallTriangle[2]->get_x(), smallTriangle[2]->get_y()));

        for(int i = 1; i < nbLastSide; i++){
            Point* p1 = linesB[2].inLine((double)i/(double)nbLastSide);
            Point* p2 = linesS[2].inLine((double)i/(double)nbLastSide);
            bigLines.push_back(p1);
            smallLines.push_back(p2);
        }

        bigLines.push_back(new Point(bigTriangle[0]->get_x(), bigTriangle[0]->get_y()));
        smallLines.push_back(new Point(smallTriangle[0]->get_x(), smallTriangle[0]->get_y()));

        // linking
        for(int i = 0; i < nbHall; i++){
            this->add_Hall( Hall(bigLines.at(i), bigLines.at((i+1) % bigLines.size()), smallLines.at(i), smallLines.at((i+1) % smallLines.size())) );
        }

    }



private:
    int width;
    int height;
    std::array<Point*, 3> bigTriangle;
    std::array<Point*, 3> smallTriangle;
    std::array<Line*, 2> medians;
};


#endif