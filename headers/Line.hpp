#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Formes.hpp"
#include "Point.hpp"

class Line : private Formes {

public:

    Line(){}

    Line(std::array<Point*, 2> points){
        this->points = points;
        a = (double) (points[1]->get_y() - points[0]->get_y()) / (double)(points[1]->get_x() - points[0]->get_x());
        b = points[0]->get_y() - (double) (a * points[0]->get_x());
    }

    Line(Point* p1, Point* p2){
        points[0] = p1;
        points[1] = p2;

        // (D): x = b (droite verticale, a devrait être à l'infini)
        if(p1->get_x() == p2->get_x()){
            a = 99999999.0;
            b = (double) p1->get_y();
        }
        // cas normal
        else {
            a = (double)( points[1]->get_y() - points[0]->get_y()) / (double)(points[1]->get_x() - points[0]->get_x());
            b = points[0]->get_y() - (double) (a * points[0]->get_x());
        }
        
    }

    Line(int x1, int y1, int x2, int y2){
        points[0] = new Point(x1, y1);
        points[1] = new Point(x2, y2);
        a = (double)( points[0]->get_y() - points[1]->get_y()) / (double)(points[0]->get_x() - points[1]->get_x());
        b = points[0]->get_y() - (double)(a * points[0]->get_x());
    }

    ~Line(){}

    void set_points(std::array<Point*, 2> points){
        this->points = points;
        a = (double)( points[0]->get_y() - points[1]->get_y()) / (double)(points[0]->get_x() - points[1]->get_x());
        b = points[0]->get_y() - (double) (a * points[0]->get_x());
    }

    void set_parameters(double a, double b){
        this->a = a;
        this->b = b;
    }

    std::array<double, 2> get_parameters(){
        return {a, b};
    }

    std::array<Point*, 2> get_points(){
        return points;
    }

    Point* get_p0(){
        return points[0];
    }

    Point* get_p1(){
        return points[1];
    }

    std::array<int, 4> get_line(){
        return {points[0]->get_x(), points[0]->get_y(), points[1]->get_x(), points[1]->get_y()};
    }

    /**
     * @brief retourne le point d'intersection avec la ligne l
     * 
     * @return Point* 
     */
    Point* intersect(Line* l){
        int x = (int) ((l->get_parameters()[1] - b) / (a - l->get_parameters()[0]));
        int y = (int) (a * x + b);
        return new Point(x, y);

    }

    /**
     * @brief retourne un point sur la ligne avec un ratio ( si ratio = 1/2, c'est le point au milieu de la ligne)
     * 
     * @return Point* 
     */
    Point* inLine(double ratio ){
        int x, y;

        if(points[0]->get_x() <= points[1]->get_x() && points[0]->get_y() <= points[1]->get_y()){
            x = (int) points[0]->get_x() + abs(points[1]->get_x() - points[0]->get_x()) * ratio;
            y = (int) points[0]->get_y() + abs(points[1]->get_y() - points[0]->get_y()) * ratio;
        }
        else if (points[0]->get_x() >= points[1]->get_x() && points[0]->get_y() >= points[1]->get_y()){
            x = (int) points[0]->get_x() - abs(points[1]->get_x() - points[0]->get_x()) * ratio;
            y = (int) points[0]->get_y() - abs(points[1]->get_y() - points[0]->get_y()) * ratio;
        }

        else if(points[0]->get_x() <= points[1]->get_x() && points[0]->get_y() >= points[1]->get_y()){
            x = (int) points[0]->get_x() + abs(points[1]->get_x() - points[0]->get_x()) * ratio;
            y = (int) points[0]->get_y() - abs(points[1]->get_y() - points[0]->get_y()) * ratio;
        }
        else if(points[0]->get_x() >= points[1]->get_x() && points[0]->get_y() <= points[1]->get_y()){
            x = (int) points[0]->get_x() - abs(points[1]->get_x() - points[0]->get_x()) * ratio;
            y = (int) points[0]->get_y() + abs(points[1]->get_y() - points[0]->get_y()) * ratio;
        }
        return new Point(x, y);
    }

    void draw(SDL_Renderer* renderer){
        SDL_RenderDrawLine(renderer, points[0]->get_x(), points[0]->get_y(), points[1]->get_x(), points[1]->get_y());
    }

private:
    std::array<Point*, 2> points;

    // paramètres de l'équation de la droite 
    double a;
    double b;
};

#endif