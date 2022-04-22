#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <SDL.h>
#include <array>
#include <tgmath.h>
#include <vector>
#include <string>
#include <memory>
#include "SDLWrapper.hpp"

class Point {

public:
    // Constructeur
    Point();

    Point( long  double x,  long  double y);
    // Point(long  double phi, long  double r);
    // Point(int x, int y, long  double phi, long  double r);
    Point(const Point &other);

    // Destructeur
    ~Point();

    void set_point (long  double x, long  double y);
    long  double get_x();
    long  double get_y();
    SDL_Point* get_point();

    // void set_polar(long  double phi, long  double r);
    // void set_cartesian(int x, int y);
    
    // std::array<long  double, 2> cartesian_to_polar(int x, int y);
    // std::array<int, 2> polar_to_cartesian(long  double phi, long  double r);

    void draw(std::shared_ptr<SDL_Renderer> renderer);
    bool get_closer();
    long  double euclideanDistance(Point p);

    bool operator==(Point&& other);
    

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