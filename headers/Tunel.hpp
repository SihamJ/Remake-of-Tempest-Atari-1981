#ifndef __TUNEL_HPP__
#define __TUNEL_HPP__

#include <vector>
#include <SDL.h>
#include <array>
#include "Line.hpp"
#include "utils.hpp"
#include "Color.hpp"

class Tunel {
    
public:
    // constructeur
    Tunel(){}

    Tunel(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
        lines[0] = Line(x1, y1, x2, y2);
        lines[1] = Line(x3, y3, x4, y4);
    }

    Tunel(Line smallLine, Line bigLine){
        lines[0] = smallLine;
        lines[1] = bigLine;
    }

    Tunel(std::array<Line, 2> lines){
        this->lines = lines;
    }

    Tunel(Point p1, Point p2, Point p3, Point p4){
        lines[0] = Line(p1, p2);
        lines[1] = Line(p3, p4);
    }

    Tunel(std::array<Point, 4> points){
        lines[0] = Line(points[0], points[1]);
        lines[1] = Line(points[2], points[3]);
    }

    // destructeur
    ~Tunel(){}

    /**
     * @brief Set the big line object
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     */
    void set_big_line (int x1, int y1, int x2, int y2) {
        lines[1] = Line(x1, y1, x2, y2);
    }

    /**
     * @brief Set the small line object
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     */
    void set_small_line (int x1, int y1, int x2, int y2) {
        lines[0] = Line(x1, y1, x2, y2);
    }

    void set_lines (std::array<Line, 2> lines){
        this->lines = lines;
    }

    /**
     * @brief Get the big line object
     * 
     * @return std::array<int, 4> 
     */
    Line get_big_line () {
        return lines[0];
    }

    /**
     * @brief Get the small line object
     * 
     * @return std::array<int, 4> 
     */
    Line get_small_line () {
        return lines[1];
    }

    std::array<Line, 2> get_lines(){
        return lines;
    }

    /**
     * @brief dessine les deux lignes
     * 
     * @param renderer 
     */
    void draw(SDL_Renderer* renderer) {
        lines[0].draw(renderer);
        lines[1].draw(renderer);
        Line l1(lines[0].get_p1(), lines[1].get_p1());
        Line l2(lines[0].get_p0(), lines[1].get_p0());
        l1.draw(renderer);
        l2.draw(renderer);
    }

private:
    // les deux lignes
    std::array<Line, 2> lines;
};

#endif