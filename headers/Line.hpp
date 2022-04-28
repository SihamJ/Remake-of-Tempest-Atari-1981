#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Point.hpp"
#include <memory>
#include <iostream>

class Line {

public:

    Line();

    Line(const std::array<Point, 2>& points);
    Line(std::array<Point, 2>&& points);
    Line(const std::array<Point, 2>& points, int thickness);
    Line(std::array<Point, 2>&& points, int thickness);

    Line(const Point& p1, const Point& p2);
    Line(Point&& p1, Point&& p2);
    Line(const Point& p1, const Point& p2, int thickness);
    Line(Point&& p1, Point&& p2, int thickness);

    Line(int x1, int y1, int x2, int y2);
    Line(int x1, int y1, int x2, int y2, int thickness);

    // Line(const Line& other);
    // Line(Line &&other);
    // Line operator=(const Line& other);
    // Line operator=(Line other);

    ~Line();



    void set_line(Point p1, Point p2);

    void set_parameters(long double a, long double b);

    const std::array<long double, 2> get_parameters() const ;

    const long double get_slope() const ;

    const std::array<Point, 2> get_points() const ;

    void set_points(std::array<Point, 2> points);

    void calculate_parameters();

    const Point get_p0() const ;

    const Point get_p1() const;

    const Line get_x_projected() const;
    const Line get_y_projected() const ;

    const int get_thickness() const ;

    void set_p0(Point p);

    void set_p1(Point p);

    void set_thickness(int thickness);

    void redefine_parameters();

    const bool is_within(Point& p) const ;

    const bool beyond_scope(Point &p)const ;

    const std::array<long double, 4> get_coord()const ;

    const Point intersect(Line l) const ;

    const long double length() const ;

    const Point inLine(long double ratio ) const ;

    void draw(std::shared_ptr<SDL_Renderer> renderer);
    void draw_shadow(std::shared_ptr<SDL_Renderer> renderer);

    const bool operator==(const Line &&l) const ;
    const bool operator!=(const Line &&l) const ;
    

private:
    std::array<Point, 2> points;

    // paramètres de l'équation de la droite 
    long double a;
    long double b;
    int thickness = 1;
};

#endif