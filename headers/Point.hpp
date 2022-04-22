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

    Point(double x, double y);
    Point(float phi, float r);
    Point(int x, int y, float phi, float r);
    Point(const Point &other);

    // Destructeur
    ~Point();

    void set_point (double x, double y);
    double get_x();
    double get_y();
    SDL_Point* get_point();

    void set_polar(float phi, float r);
    void set_cartesian(int x, int y);
    
    std::array<float, 2> cartesian_to_polar(int x, int y);
    std::array<int, 2> polar_to_cartesian(float phi, float r);

    void draw(std::shared_ptr<SDL_Renderer> renderer);
    bool get_closer();
    double euclideanDistance(Point p);

    bool operator==(Point&& other);
    

private:

    SDL_Point p;
    // coordonnées cartésiennes
    double x;
    double y;

    int thickness = 5;

    //coordonnées polaires
    float phi;
    float r;

};

#endif