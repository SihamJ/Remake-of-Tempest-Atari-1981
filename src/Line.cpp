#include "../headers/Line.hpp"


Line::Line(){}

Line::Line(std::array<Point, 2> points){
    this->points = points;

    calculate_parameters();
}

Line::Line(Point p1, Point p2){
    points[0] = p1;
    points[1] = p2;

    calculate_parameters();
    
}

Line::Line(int x1, int y1, int x2, int y2){
    points[0].set_point(x1, y1);
    points[1].set_point(x2, y2);

    calculate_parameters();
}

Line::~Line(){}



void Line::set_line(Point p1, Point p2){
    this->points[0] = p1;
    this->points[1] = p2;
    a = (double)( p1.get_y() - p2.get_y()) / (double)(p1.get_x() - p2.get_x());
    b = p1.get_y() - (double) (a * p1.get_x());
}

void Line::set_parameters(double a, double b){
    this->a = a;
    this->b = b;
}

std::array<double, 2> Line::get_parameters(){
    return {a, b};
}

double Line::get_slope(){
    return this->a;
}

std::array<Point, 2> Line::get_points(){
    return points;
}

void Line::set_points(std::array<Point, 2> points){
    this->points = points;
}

void Line::calculate_parameters(){
    // (D): x = b (droite verticale, a devrait être à l'infini)
    if(points[0].get_x() == points[1].get_x()){
        a = 99999999.0;
        b = (double) points[0].get_y();
    }
    // cas normal
    else {
        a = (double)( points[1].get_y() - points[0].get_y()) / (double)(points[1].get_x() - points[0].get_x());
        b = points[0].get_y() - (double) (a * points[0].get_x());
    }
}

Point Line::get_p0(){
    return points[0];
}

Point Line::get_p1(){
    return points[1];
}

Line Line::get_x_projected(){
    return Line { static_cast<int>(this->get_p0().get_x()), 0, static_cast<int>(this->get_p1().get_x()), 0 };
}

Line Line::get_y_projected(){
    return Line { 0, static_cast<int>(this->get_p0().get_y()), 0, static_cast<int>(this->get_p1().get_y()) };
}

void Line::set_p0(Point p){
    this->points[0] = p;
}

void Line::set_p1(Point p){
    this->points[1] = p;
}

bool Line::is_within(Point& p){
        
    double a = this->get_slope();

    bool on = (p.get_y() - this->get_p0().get_y()) == a * (p.get_x() - this->get_p0().get_x());

    double max_y = this->get_p1().get_y() > this->get_p0().get_y() ? this->get_p1().get_y() : this->get_p0().get_y();
    double min_y = this->get_p1().get_y() < this->get_p0().get_y() ? this->get_p1().get_y() : this->get_p0().get_y();
    double max_x = this->get_p1().get_x() > this->get_p0().get_x() ? this->get_p1().get_x() : this->get_p0().get_x();
    double min_x = this->get_p1().get_x() < this->get_p0().get_x() ? this->get_p1().get_x() : this->get_p0().get_x();

    bool between = ( min_y <= p.get_y() <= max_y && min_x <= p.get_x() <= max_x);

    return (on && between); 
}

bool Line::beyond_scope(Point &p){
    double max_y = this->get_p1().get_y() > this->get_p0().get_y() ? this->get_p1().get_y() : this->get_p0().get_y();
    double min_y = this->get_p1().get_y() < this->get_p0().get_y() ? this->get_p1().get_y() : this->get_p0().get_y();
    double max_x = this->get_p1().get_x() > this->get_p0().get_x() ? this->get_p1().get_x() : this->get_p0().get_x();
    double min_x = this->get_p1().get_x() < this->get_p0().get_x() ? this->get_p1().get_x() : this->get_p0().get_x();
    bool res= !( min_y <= p.get_y() &&  p.get_y() <= max_y && min_x <= p.get_x() && p.get_x() <= max_x);

    return res;
}

void Line::redefine_parameters(){
    // (D): x = b (droite verticale, a devrait être à l'infini)
    if(points[0].get_x() == points[1].get_x()){
        this->a = 99999999.0;
        this->b = (double) points[0].get_y();
    }
    // cas normal
    else {
        this->a = (double)( points[1].get_y() - points[0].get_y()) / (double)(points[1].get_x() - points[0].get_x());
        this->b = points[0].get_y() - (double) (this->a * points[0].get_x());
    }
}

std::array<double, 4> Line::get_coord(){
    return {points[0].get_x(), points[0].get_y(), points[1].get_x(), points[1].get_y()};
}

/**
 * @brief retourne le point d'intersection avec la droite passant par la ligne l
 * 
 * @return Point* 
 */
Point Line::intersect(Line l){
    Point p;

    // To Do: que faire avec deux droites parallèles ? et pq ca arrive dans les flippers ?
    if(a == l.get_parameters()[0]){
        return this->get_p0();
    }
    int x = (int) ((l.get_parameters()[1] - b) / (a - l.get_parameters()[0]));
    int y = (int) (a * x + b);
    p.set_point(x, y);
    return p;

}

double Line::length(){
    return  this->get_p0().euclideanDistance(this->get_p1());
}

/**
 * @brief retourne un point sur la ligne avec un ratio ( si ratio = 1/2, c'est le point au milieu de la ligne)
 * 
 * @return Point
 */
Point Line::inLine(double ratio ){
    double x, y;
    double coeff1 = points[0].get_x() <= points[1].get_x() ? 1. : -1.;
    double coeff2 = points[0].get_y() <= points[1].get_y() ? 1. : -1.;

    x = (double)points[0].get_x() + (double)(coeff1 * abs(points[1].get_x() - points[0].get_x())) * ratio;
    y = (double)points[0].get_y() + (double)(coeff2 * abs(points[1].get_y() - points[0].get_y())) * ratio;

    return Point{x,y};
}

void Line::draw(std::shared_ptr<SDL_Renderer> renderer){
    SDL_RenderDrawLine(renderer.get(), points[0].get_x(), points[0].get_y(), points[1].get_x(), points[1].get_y());
}

