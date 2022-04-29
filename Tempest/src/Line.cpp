#include "Line.hpp"


Line::Line(){}

Line::Line(const std::array<Point, 2>& points){
    this->points = points;
    calculate_parameters();
}

Line::Line(const std::array<Point, 2>& points, int thickness){
    this->points = points;
    this->thickness = thickness;
    calculate_parameters();
}

Line::Line(std::array<Point, 2>&& points){
    this->points = std::move(points);
    calculate_parameters();
}

Line::Line(std::array<Point, 2>&& points, int thickness){
    this->points = std::move(points);
    this->thickness = thickness;
    calculate_parameters();
}

Line::Line(const Point& p1, const Point& p2){
    points[0] = p1;
    points[1] = p2;
    calculate_parameters();
}

Line::Line(const Point& p1, const Point& p2, int thickness){
    points[0] = p1;
    points[1] = p2;
    this->thickness = thickness;
    calculate_parameters();
}

Line::Line(Point&& p1, Point&& p2){
    points[0] = std::move(p1);
    points[1] = std::move(p2);
    calculate_parameters();
}

Line::Line(Point&& p1, Point&& p2, int thickness){
    points[0] = std::move(p1);
    points[1] = std::move(p2);
    this->thickness = thickness;
    calculate_parameters();
}

Line::Line(int x1, int y1, int x2, int y2){
    points[0].set_point(x1, y1);
    points[1].set_point(x2, y2);
    calculate_parameters();
}

Line::Line(int x1, int y1, int x2, int y2, int thickness){
    points[0].set_point(x1, y1);
    points[1].set_point(x2, y2);
    this->thickness = thickness;
    calculate_parameters();
}

// Line::Line(const Line& other){
//     this->points = other.points;
//     this->thickness = other.thickness;
//     calculate_parameters();
// }

// Line::Line(Line &&other){
//     this->points = other.points;
//     this->thickness = other.thickness;
//     calculate_parameters();
// }

// Line Line::operator=(const Line& other){
//     return Line(other.points, other.thickness);
// }

// Line Line::operator=(Line other){
//     return Line(other.points, other.thickness);
// }



Line::~Line(){}


void Line::set_line(Point p1, Point p2){
    this->points[0] = p1;
    this->points[1] = p2;
    a = (long double)( p1.get_y() - p2.get_y()) / (long double)(p1.get_x() - p2.get_x());
    b = p1.get_y() - (long double) (a * p1.get_x());
}

void Line::set_parameters(long double a, long double b){
    this->a = a;
    this->b = b;
}

const std::array<long double, 2> Line::get_parameters() const {
    return {a, b};
}

const long double Line::get_slope() const {
    return this->a;
}

const std::array<Point, 2> Line::get_points() const {
    return points;
}

void Line::set_points(std::array<Point, 2> points){
    this->points = points;
}

void Line::calculate_parameters(){
    // (D): x = b (droite verticale, a devrait être à l'infini)
    if(points[0].get_x() == points[1].get_x()){
        a = 99999999.0;
        b = points[0].get_y();
    }
    // cas normal
    else {
        a = ( points[1].get_y() - points[0].get_y()) / (points[1].get_x() - points[0].get_x());
        b = points[0].get_y() - (a * points[0].get_x());
    }
}

const  Point Line::get_p0() const {
    return points[0];
}

const Point Line::get_p1() const {
    return points[1];
}

const Line Line::get_x_projected() const {
    const Point p0 = this->get_p0();
    const Point p1 = this->get_p1();
    return Line { static_cast<int>(p0.get_x()), 0, static_cast<int>(p1.get_x()), 0 };
}

const Line Line::get_y_projected() const {
    const Point p0 = this->get_p0();
    const Point p1 = this->get_p1();
    return Line { 0, static_cast<int>(p0.get_y()), 0, static_cast<int>(p1.get_y()) };
}

const  int Line::get_thickness() const {
    return this->thickness;
}

void Line::set_p0(Point p){
    this->points[0] = p;
}

void Line::set_p1(Point p){
    this->points[1] = p;
}

void Line::set_thickness(int thickness){
    this->thickness = thickness;
}

const bool Line::is_within(Point& p)const {

    const Point p0 = this->get_p0();
    const Point p1 = this->get_p1();
        
    long double a = this->get_slope();

    bool on = (p.get_y() - p0.get_y()) == a * (p.get_x() - p0.get_x());

    long double max_y = p1.get_y() > p0.get_y() ? p1.get_y() : p0.get_y();
    long double min_y = p1.get_y() < p0.get_y() ? p1.get_y() : p0.get_y();
    long double max_x = p1.get_x() > p0.get_x() ? p1.get_x() : p0.get_x();
    long double min_x = p1.get_x() < p0.get_x() ? p1.get_x() : p0.get_x();

    bool between = ( min_y <= p.get_y() <= max_y && min_x <= p.get_x() <= max_x);

    return (on && between); 
}

const bool Line::beyond_scope(Point &p)const {

    const Point p0 = this->get_p0();
    const Point p1 = this->get_p1();

    long double max_y = p1.get_y() > p0.get_y() ? p1.get_y() : p0.get_y();
    long double min_y = p1.get_y() < p0.get_y() ? p1.get_y() : p0.get_y();
    long double max_x = p1.get_x() > p0.get_x() ? p1.get_x() : p0.get_x();
    long double min_x = p1.get_x() < p0.get_x() ? p1.get_x() : p0.get_x();
    bool res= !( min_y <= p.get_y() &&  p.get_y() <= max_y && min_x <= p.get_x() && p.get_x() <= max_x);

    return res;
}

void Line::redefine_parameters(){
    // (D): x = b (droite verticale, a devrait être à l'infini)
    if(points[0].get_x() == points[1].get_x()){
        this->a = 99999999.0;
        this->b = (long double) points[0].get_y();
    }
    // cas normal
    else {
        this->a = (long double)( points[1].get_y() - points[0].get_y()) / (long double)(points[1].get_x() - points[0].get_x());
        this->b = points[0].get_y() - (long double) (this->a * points[0].get_x());
    }
}

const std::array<long double, 4> Line::get_coord()const {
    return {points[0].get_x(), points[0].get_y(), points[1].get_x(), points[1].get_y()};
}

/**
 * @brief retourne le point d'intersection avec la droite passant par la ligne l
 * 
 * @return Point* 
 */
const Point Line::intersect(Line l)const {
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

const long double Line::length()const {
    return  this->get_p0().euclideanDistance(this->get_p1());
}

/**
 * @brief retourne un point sur la ligne avec un ratio ( si ratio = 1/2, c'est le point au milieu de la ligne)
 * 
 * @return Point
 */
const Point Line::inLine(long double ratio )const {
    long double x, y;
    long double coeff1 = points[0].get_x() <= points[1].get_x() ? 1. : -1.;
    long double coeff2 = points[0].get_y() <= points[1].get_y() ? 1. : -1.;

    x = points[0].get_x() + coeff1 * abs(points[1].get_x() - points[0].get_x()) * ratio;
    y = points[0].get_y() + coeff2 * abs(points[1].get_y() - points[0].get_y()) * ratio;

    return Point{ x, y};
}

void Line::draw(std::shared_ptr<SDL_Renderer> renderer){

    int xstep = 0;
    int ystep = 0;

    if(this->get_y_projected().length() >= 0 && this->get_y_projected().length() > this->get_x_projected().length())
        xstep++;

    else if(this->get_x_projected().length() >= 0 && this->get_y_projected().length() < this->get_x_projected().length())
        ystep++;

    else if(this->get_y_projected().length() == this->get_x_projected().length() && (this->get_y_projected().length() > 0 || this->get_x_projected().length()))
    {
        xstep++;
        ystep++;
    }
    else 
        return;
    
    for(int i = 0, j=0 ; i < this->thickness && j < this->thickness; i +=xstep, j+=ystep)
        SDL_RenderDrawLine(renderer.get(), points[0].get_x()+i, points[0].get_y()+j, points[1].get_x()+i, points[1].get_y()+j);
}

void Line::draw_shadow(std::shared_ptr<SDL_Renderer> renderer){

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer.get(), &r, &g, &b, &a);

    int xstep = 0;
    int ystep = 0;
    int x1start = points[0].get_x();
    int y1sart = points[0].get_y();
    int x2start = points[1].get_x();
    int y2start = points[1].get_y();

    if(this->get_y_projected().length() >= 0 && this->get_y_projected().length() > this->get_x_projected().length())
        xstep++;

    else if(this->get_x_projected().length() >= 0 && this->get_y_projected().length() < this->get_x_projected().length())
        ystep++;

    else if(this->get_y_projected().length() == this->get_x_projected().length() && (this->get_y_projected().length() > 0 || this->get_x_projected().length()))
    {
        xstep++;
        ystep++;
    }
    else 
        return;
    SDL_SetRenderDrawColor(renderer.get(), 0, 80, 40, 255);
    for(int i = 0, j=0 ; i < this->thickness && j < this->thickness; i +=xstep, j+=ystep)
        SDL_RenderDrawLine(renderer.get(), x1start-i, y1sart-j, x2start-i, y2start-j);
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

const bool Line::operator==(const Line &&l) const {
    return (this->get_p0() == std::move(l.get_p0()) && this->get_p1() == std::move(l.get_p1()));
}

const bool Line::operator!=(const Line &&l) const {
    return (this->get_p0() != std::move(l.get_p0()) || this->get_p1() != std::move(l.get_p1()));
}