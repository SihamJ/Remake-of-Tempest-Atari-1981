#include "TriangleMap.hpp"


TriangleMap::TriangleMap(){}

TriangleMap::TriangleMap(const int nbHall, Color&& c)
    : Tube("Triangle", nbHall, std::move(c))
{
        this->width = 2*WIDTH/5;
        this->height = 5*HEIGHT/7;

        set_big_triangle();

        // On calcule de 2 -lignes- médianes du triangles
        set_medians();

        // On determine le barycentre (intersection de deux médianes)
        // il servira par la suite comme point central pour les missiles ennemis
        this->center = medians[0].intersect(medians[1]);

        // On peut maintenant définir le triangle intérieur
        set_small_triangle(0.6);
    }

//destructeur
TriangleMap::~TriangleMap(){}

// coordonnées du triangle extérieur
void TriangleMap::set_big_triangle(){
    // Base du triangle
    bigTriangle[0].set_point(WIDTH/2 - this->width/2, HEIGHT/2 + this->height/2);
    bigTriangle[1].set_point(WIDTH/2 + this->width/2, HEIGHT/2 + this->height/2);

    // Point supérieur
    bigTriangle[2].set_point(WIDTH/2, HEIGHT/2 - this->height/2);
}

// médianes du triangle
void TriangleMap::set_medians(){
    Point mid_1 = Point( WIDTH/2 - abs(bigTriangle[2].get_x() - bigTriangle[0].get_x()) / 2, bigTriangle[2].get_y() + abs( bigTriangle[0].get_y() - bigTriangle[2].get_y()) / 2);
    Point mid_2 = Point( WIDTH/2 + abs(bigTriangle[2].get_x() - bigTriangle[1].get_x() ) / 2, bigTriangle[2].get_y() + abs( bigTriangle[1].get_y() - bigTriangle[2].get_y() ) / 2);
    Point mid_3 = Point( WIDTH/2, bigTriangle[0].get_y());

    medians[0].set_line(bigTriangle[0], mid_2);
    medians[1].set_line(bigTriangle[1], mid_1);
}

// calcul des coordonnées du triangle intérieur
void TriangleMap::set_small_triangle(const long  double ratio){
    smallTriangle[0] = medians[0].inLine(ratio);
    smallTriangle[1] = medians[1].inLine(ratio);
    smallTriangle[2].set_point(bigTriangle[2].get_x(), bigTriangle[2].get_y() + abs(bigTriangle[0].get_y() - bigTriangle[2].get_y())*ratio);
}


// Constructions des couloirs
void TriangleMap::build_map(){
    int hallPerSide = nbHall / 3;
    int nbLastSide = hallPerSide + nbHall % 3;
    std::vector<Point> bigLines;
    std::vector<Point> smallLines;

    std::array<Line, 3> linesB;
    std::array<Line, 3> linesS;

    for(int i = 0; i < 3; i++){
        linesB[i].set_line(bigTriangle[i], bigTriangle[(i+1)%3]);
        linesS[i].set_line(smallTriangle[i], smallTriangle[(i+1)%3]);
    }
    
    bigLines.push_back( Point(bigTriangle[0].get_x(), bigTriangle[0].get_y()));
    smallLines.push_back( Point(smallTriangle[0].get_x(), smallTriangle[0].get_y()));

    for(int i = 1; i < hallPerSide; i++){
        Point p1 = linesB[0].inLine(static_cast<long  double>(i)/static_cast<long  double>(hallPerSide));
        Point p2 = linesS[0].inLine(static_cast<long  double>(i)/static_cast<long  double>(hallPerSide));
        bigLines.push_back(p1);
        smallLines.push_back(p2);
    }

    bigLines.push_back( Point(bigTriangle[1].get_x(), bigTriangle[1].get_y()));
    smallLines.push_back( Point(smallTriangle[1].get_x(), smallTriangle[1].get_y()));

    for(int i = 1; i < hallPerSide; i++){
        Point p1 = linesB[1].inLine( static_cast<long  double>(i)/static_cast<long  double>(hallPerSide));
        Point p2 = linesS[1].inLine(static_cast<long  double>(i)/static_cast<long  double>(hallPerSide));
        bigLines.push_back(p1);
        smallLines.push_back(p2);
    }

    bigLines.push_back(Point(bigTriangle[2].get_x(), bigTriangle[2].get_y()));
    smallLines.push_back(Point(smallTriangle[2].get_x(), smallTriangle[2].get_y()));

    for(int i = 1; i < nbLastSide; i++){
        Point p1 = linesB[2].inLine(static_cast<long  double>(i)/static_cast<long  double>(nbLastSide));
        Point p2 = linesS[2].inLine(static_cast<long  double>(i)/static_cast<long  double>(nbLastSide));
        bigLines.push_back(p1);
        smallLines.push_back(p2);
    }

    bigLines.push_back(Point(bigTriangle[0].get_x(), bigTriangle[0].get_y()));
    smallLines.push_back(Point(smallTriangle[0].get_x(), smallTriangle[0].get_y()));

    // linking
    for(int i = 0; i < nbHall; i++){
        Tunel h = Tunel(std::move(bigLines.at(i)), std::move(bigLines.at((i+1) % bigLines.size())), std::move(smallLines.at(i)), std::move(smallLines.at((i+1) % smallLines.size())), this->thickness);
        h.set_angle();
        h.set_nb_hall(i);
        this->add_Hall(std::move(h));
    }

}
