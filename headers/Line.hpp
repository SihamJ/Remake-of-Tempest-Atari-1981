#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Point.hpp"
#include <memory>
#include <iostream>

class Line {

public:

    Line();

    Line(std::array<Point, 2> points);

    Line(Point p1, Point p2);

    Line(int x1, int y1, int x2, int y2);

    ~Line();



    void set_line(Point p1, Point p2);

    void set_parameters(double a, double b);

    std::array<double, 2> get_parameters();

    double get_slope();

    std::array<Point, 2> get_points();

    void set_points(std::array<Point, 2> points);

    void calculate_parameters();

    Point get_p0();

    Point get_p1();

    void set_p0(Point p);

    void set_p1(Point p);

    void redefine_parameters();

    bool is_within(Point& p);

    bool beyond_scope(Point &p);

    std::array<double, 4> get_coord();

    /**
     * @brief retourne le point d'intersection avec la droite passant par la ligne l
     * 
     * @return Point* 
     */
    Point intersect(Line l);

    double length();
    /**
     * @brief retourne un point sur la ligne avec un ratio ( si ratio = 1/2, c'est le point au milieu de la ligne)
     * 
     * @return Point
     */
    Point inLine(double ratio );

    void draw(std::shared_ptr<SDL_Renderer> renderer);

private:
    std::array<Point, 2> points;

    // paramètres de l'équation de la droite 
    double a;
    double b;
};

#endif