#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <SDL.h>
#include <array>
#include <tgmath.h>
#include <vector>
#include <string>
#include <memory>
#include "SDLWrapper.hpp"
#include "Utils.hpp"

class Point {

public:
    // Constructeur
    Point();

    Point( long  double x,  long  double y);
    Point(const Point &other);
    ~Point();

    
    const long  double get_x() const;
    const long  double get_y() const;
    std::shared_ptr<SDL_Point> get_point() const;

    void set_point (long  double x, long  double y);
    
    std::array<long  double, 2> cartesian_to_polar();
    std::array<long  double, 2> polar_to_cartesian(long  double phi, long  double r);

    void draw(std::shared_ptr<SDL_Renderer> renderer);
    bool get_closer();
    const long  double euclideanDistance(Point p) const ;

    const bool operator==(const Point&& other) const ;
    Point operator-(const Point &other) ;
    const bool operator!=(const Point &other) const;


    const Point get_point_from_rotation(Point center, double angle);

    void rotate(const Point Pivot, const long double Angle);
    

private:

    SDL_Point p;
    // coordonnées cartésiennes
     long  double x;
     long  double y;

    int thickness = 5;

    //coordonnées polaires
    long  double phi;
    long  double r;

};

#endif