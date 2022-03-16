#ifndef __HALL_HPP__
#define __HALL_HPP__

#include <vector>
#include <SDL.h>
#include <array>
#include "Line.hpp"

class Hall : private Formes {
    
public:
    // constructeur
    Hall(){}

    Hall(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
        lines[0] = new Line(x1, y1, x2, y2);
        lines[1] = new Line(x3, y3, x4, y4);
    }

    Hall(Line* smallLine, Line* bigLine){
        lines[0] = smallLine;
        lines[1] = bigLine;
    }

    Hall(std::array<Line*, 2> lines){
        this->lines = lines;
    }

    Hall(Point* p1, Point* p2, Point* p3, Point* p4){
        lines[0] = new Line(p1, p2);
        lines[1] = new Line(p3, p4);
    }

    Hall(std::array<Point*, 4> points){
        lines[0] = new Line(points[0], points[1]);
        lines[1] = new Line(points[2], points[3]);
    }

    // destructeur
    ~Hall(){}

    /**
     * @brief Set the big line object
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     */
    void set_big_line (int x1, int y1, int x2, int y2) {
        bigLine = {x1, y1, x2, y2};
        lines[1] = new Line(x1, y1, x2, y2);
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
        smallLine = {x1, y1, x2, y2};
        lines[0] = new Line(x1, y1, x2, y2);
    }

    void set_lines (std::array<Line*, 2> lines){
        this->lines = lines;
    }

    /**
     * @brief Get the big line object
     * 
     * @return std::array<int, 4> 
     */
    std::array<int, 4> get_big_line () {
        // return bigLine;
        return lines[1]->get_line();
    }

    /**
     * @brief Get the small line object
     * 
     * @return std::array<int, 4> 
     */
    std::array<int, 4> get_small_line () {
        //return smallLine;
        return lines[0]->get_line();
    }

    std::array<Line*, 2> get_lines(){
        return lines;
    }

    /**
     * @brief dessine les deux lignes
     * 
     * @param renderer 
     */
    void draw(SDL_Renderer* renderer) {
        lines[0]->draw(renderer);
        lines[1]->draw(renderer);
    }

private:
    // la petite ligne intérieur qui forme un couloir
    std::array<int, 4> bigLine;
    // la gross ligne extérieur qui forme un couloir
    std::array<int, 4> smallLine;
    // les deux lignes
    std::array<Line*, 2> lines;
};

#endif