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
    Tunel(){}

    Tunel(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
        lines[0] = Line(x1, y1, x2, y2);
        lines[1] = Line(x3, y3, x4, y4);
    }

    Tunel(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int thickness){
        lines[0] = Line(x1, y1, x2, y2, thickness);
        lines[1] = Line(x3, y3, x4, y4, thickness);
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

    Tunel(Point p1, Point p2, Point p3, Point p4, int thickness){
        lines[0] = Line(p1, p2, thickness);
        lines[1] = Line(p3, p4, thickness);
    }

    Tunel(std::array<Point, 4> points){
        lines[0] = Line(points[0], points[1]);
        lines[1] = Line(points[2], points[3]);
    }
    
    Tunel(std::array<Point, 4> points, int thickness){
        lines[0] = Line(points[0], points[1], thickness);
        lines[1] = Line(points[2], points[3], thickness);
    }

    // destructeur
    ~Tunel(){}

    void set_big_line (int x1, int y1, int x2, int y2) {
        lines[1] = Line(x1, y1, x2, y2);
    }

    void set_small_line (int x1, int y1, int x2, int y2) {
        lines[0] = Line(x1, y1, x2, y2);
    }

    void set_lines (std::array<Line, 2> lines){
        this->lines = lines;
    }

    void set_angle(){

        Line s = this->get_small_line();
        long double x1, x2, y1, y2;
        x1 = s.get_p0().get_x();
        y1 = s.get_p0().get_y();
        x2 = s.get_p1().get_x();
        y2 = s.get_p1().get_y();      

        this->angle = atan2( y2 - y1, x2 - x1);

        this->angle = this->angle * (180.0/3.141592653589793238463);

        if(this->get_small_line().get_x_projected().length() == 0 || this->get_small_line().get_y_projected().length() == 0)
            this->angle = 180. + this->angle;
        
         if (this->angle < 0) this->angle += 360.;
    }
    
    const long double get_angle(Tunel h) const {

        if(this->parallel(h)){
            return 180.;
        }

        Point ab { h.get_small_line().get_p1().get_x() - h.get_small_line().get_p0().get_x(), 
                    h.get_small_line().get_p1().get_y() - h.get_small_line().get_p0().get_y()};
        Point cb { h.get_small_line().get_p1().get_x() - this->get_small_line().get_p1().get_x(), 
                    h.get_small_line().get_p1().get_y() - this->get_small_line().get_p1().get_y()};

        float dot = ab.get_x() * cb.get_x() + ab.get_y()*cb.get_y();
        float cross = ab.get_x()*cb.get_y() - ab.get_y()*cb.get_x();

        float angle = atan2(cross, dot) * (180. / PI);
        if (angle < 0) angle += 360.;

        return angle;
        
    }

    const bool parallel(Tunel h) const {
        // same slope
        return this->get_small_line().get_parameters().at(0) == h.get_small_line().get_parameters().at(0);
    }

    /*
    int CGlEngineFunctions::GetAngleABC( POINTFLOAT a, POINTFLOAT b, POINTFLOAT c )
{
    POINTFLOAT ab = { b.x - a.x, b.y - a.y };
    POINTFLOAT cb = { b.x - c.x, b.y - c.y };

    float dot = (ab.x * cb.x + ab.y * cb.y); // dot product
    float cross = (ab.x * cb.y - ab.y * cb.x); // cross product

    float alpha = atan2(cross, dot);

    return (int) floor(alpha * 180. / pi + 0.5);
}
    */

    const long  double get_angle() const {
        return this->angle;
    }

    void set_nb_hall(int index) { this->nb_hall = index;}

    const Line get_big_line () const {
        return lines.at(0);
    }

    const Line get_small_line () const {
        return lines.at(1);
    }

    const std::array<Line, 2> get_lines() const {
        return lines;
    }

    const int get_n_hall() const { return this->nb_hall; }

    const long  double length() const {
        Line s = this->lines.at(1);
        Line b = this->lines.at(0);
        return s.inLine(0.5).euclideanDistance(b.inLine(0.5));
    }


    void draw(std::shared_ptr<SDL_Renderer> renderer) {
        lines[0].draw(renderer);
        lines[1].draw(renderer);
        Line l1(lines[0].get_p1(), lines[1].get_p1(), lines[0].get_thickness());
        Line l2(lines[0].get_p0(), lines[1].get_p0(), lines[0].get_thickness());
        l1.draw(renderer);
        l2.draw(renderer);
    }

    void draw_shadow(std::shared_ptr<SDL_Renderer> renderer) {
        lines[0].draw_shadow(renderer);
        lines[1].draw_shadow(renderer);
        Line l1(lines[0].get_p1(), lines[1].get_p1(), lines[0].get_thickness());
        Line l2(lines[0].get_p0(), lines[1].get_p0(), lines[0].get_thickness());
        l1.draw_shadow(renderer);
        l2.draw_shadow(renderer);
    }
    
    const bool operator==(Tunel &&t) const {
        return (this->get_small_line() == std::move(t.get_small_line()) && this->get_big_line() == std::move(t.get_big_line()));
    }

    const bool operator!=(Tunel &&t) const {
        return (this->get_small_line() != std::move(t.get_small_line()) || this->get_big_line() != std::move(t.get_big_line()));
    }


private:
    // les deux lignes
    std::array<Line, 2> lines;
    int nb_hall;
    long  double angle;
};

#endif