#ifndef __TRIANGLEMAP_HPP__
#define __TRIANGLEMAP_HPP__

#include "Tube.hpp"

class TriangleMap : public Tube {

public:

    TriangleMap();
    
    TriangleMap(const int nbHall, const int width, const int height, const Color c);

    //destructeur
    ~TriangleMap();

    // coordonnées du triangle extérieur
    void set_big_triangle(const int width, const int height);

    // médianes du triangle
    void set_medians(const int width);

    // calcul des coordonnées du triangle intérieur
    void set_small_triangle(const double ratio);

    // Constructions des couloirs
    void build_map() override;



private:

    std::array<Point, 3> bigTriangle;
    std::array<Point, 3> smallTriangle;
    std::array<Line, 2> medians;
};


#endif