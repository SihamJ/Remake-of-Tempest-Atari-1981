#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Formes.hpp"
#include "Point.hpp"

class Line : private Formes {

public:

    Line(){}

    Line(std::array<Point*, 2> points){
        this->points = points;
        a = ( points[0].get_y() - points[1].get_y()) / (points[0].get_x() - points[1].get_x());
        b = points[0].get_y() - a * points[0].get_x();
    }

    Line(Point* p1, Point* p2){
        points[0] = p1;
        points[1] = p2;
        a = ( points[0].get_y() - points[1].get_y()) / (points[0].get_x() - points[1].get_x());
        b = points[0].get_y() - a * points[0].get_x();
    }

    Line(int x1, int y1, int x2, int y2){
        points[0] = new Point(x1, y1);
        points[1] = new Point(x2, y2);
        a = ( points[0].get_y() - points[1].get_y()) / (points[0].get_x() - points[1].get_x());
        b = points[0].get_y() - a * points[0].get_x();
    }

    ~Line(){}

    void set_points(std::array<Point*, 2> points){
        this->points = points;
        a = ( points[0].get_y() - points[1].get_y()) / (points[0].get_x() - points[1].get_x());
        b = points[0].get_y() - a * points[0].get_x();
    }

    void set_parameters(int a, int b){
        this->a = a;
        this->b = b;
    }

    std::array<int, 2> get_parameters(){
        return {a, b};
    }

    std::array<Point*, 2> get_points(){
        return points;
    }

    // Point d'intersection avec une autre ligne
    Point* intersect(Line* l){

        int x = (l->get_parameters()[1] - b) / (l->get_parameters()[0] - a);
        int y = a * x + b;

        return new Point(x, y);

    }

    Point* inLine(double ratio ){
        int x = (int) points[0].get_x() + (points[1].get_x() - points[0].get_x()) * ratio;
        int y = (int) points[0].get_y() + (points[1].get_y() - points[0].get_y()) * ratio;
        return new Point(x, y);
    }

    void draw(SDL_Renderer* renderer){
        SDL_RenderDrawLine(renderer, points[0]->get_x(), points[0]->get_y(), points[1]->get_x(), points[1]->get_y());
    }

private:
    std::array<Point*, 2> points;

    // equation parameters
    int a;
    int b;
};

#endif