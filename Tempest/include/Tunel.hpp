#ifndef __TUNEL_HPP__
#define __TUNEL_HPP__

#include <vector>
#include <SDL.h>
#include <array>
#include "Line.hpp"
#include "Utils.hpp"
#include "Color.hpp"

class Tunel {
    
public:
    // constructeur
    Tunel();

    Tunel(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    Tunel(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int thickness);
    Tunel(Line&& smallLine, Line&& bigLine);
    Tunel(std::array<Line, 2>&& lines);
    Tunel(Point&& p1, Point&& p2, Point&& p3, Point&& p4);
    Tunel(Point&& p1, Point&& p2, Point&& p3, Point&& p4, int thickness);
    Tunel(std::array<Point, 4>&& points);
    Tunel(std::array<Point, 4>&& points, int thickness);

    // destructeur
    ~Tunel();
    
    const long double get_angle(Tunel h) const;
    const long  double get_angle() const ;
    const Line get_big_line () const ;
    const Line get_small_line () const;
    const std::array<Line, 2> get_lines() const ;
    const int get_n_hall() const ;

    void set_big_line (int x1, int y1, int x2, int y2);
    void set_small_line (int x1, int y1, int x2, int y2);
    void set_big_line (Line l);
    void set_small_line (Line l);
    void set_lines (std::array<Line, 2> lines);
    void set_angle();
    void set_nb_hall(int index);

    const long  double length() const;
    const bool parallel(Tunel h) const;

    void draw(std::shared_ptr<SDL_Renderer> renderer) ;
    void draw_shadow(std::shared_ptr<SDL_Renderer> renderer);
    
    const bool operator==(Tunel &&t) const ;
    const bool operator!=(Tunel &&t) const;


private:
    // les deux lignes
    std::array<Line, 2> lines;
    int nb_hall;
    long  double angle;
};

#endif