#include "../headers/Point.hpp"

    Point::Point(){}

    Point::Point( long  double x, long  double y){
        p.x = x;
        p.y = y;
        this->x = x;
        this->y = y;
    }

    // Point::Point(long  double phi, long  double r){
    //     this->phi = phi;
    //     this->r = r;
    // }

    // Point::Point(int x, int y, long  double phi, long  double r){
    //     p.x = x;
    //     p.y = y;
    //     this->x = x;
    //     this->y = y;
    //     this->phi = phi;
    //     this->r = r;
    // }


    Point::Point(const Point &other)
        : x(other.x), y(other.y), phi(other.phi), r(other.r), p(other.p)
    {
        p.x = other.x;
        p.y = other.y;
    }

    Point::~Point(){}

    SDL_Point* Point::get_point(){
        SDL_Point* p = new SDL_Point(this->p);
        return p;
    }

    bool Point::operator==(Point&& other){
        return (this->get_x() == other.get_x() && this->get_y() == other.get_y());
    }

    

    void Point::set_point (long  double x, long  double y) {
        this->p.x = x;
        this->p.y = y;
        this->x = x;
        this->y = y;
    }

    long  double Point::get_x(){
        return this->x;
    }

    long  double Point::get_y(){
        return this->y;
    }

    // void Point::set_polar(long  double phi, long  double r){
    //     this->phi = phi;
    //     this->r = r;
    // }

    // void Point::set_cartesian(int x, int y){
    //     this->x = x;
    //     this->y = y;
    // }
    
    // std::array<long  double, 2> Point::cartesian_to_polar(int x, int y){
    //     long  double phi, r;
    //     long  double xx = static_cast<long  double>(x);
    //     long  double yy = static_cast<long  double>(y);

    //     if(x == 0){
    //         if(y == 0)
    //             return {0, 0};
    //         // assumption: x and y coordinates are always positive
    //         phi = 1.5708;
    //     }
    //     else
    //         phi = atan(yy/xx);

    //     r = sqrt(xx*xx + yy*yy);
    //     return { phi, r};
    // }

    // std::array<int, 2> Point::polar_to_cartesian(long  double phi, long  double r){
    //     int x, y;
    //     x = static_cast<int>( r * cos(phi));
    //     y = static_cast<int>( r * sin(phi));
    //     return {x, y};
    // }


    void Point::draw( std::shared_ptr<SDL_Renderer> renderer) {
        for(int i =0; i<this->thickness; i++){
            SDL_RenderDrawPoint(renderer.get(), p.x+i, p.y);
            SDL_RenderDrawPoint(renderer.get(), p.x+i, p.y+i);
            SDL_RenderDrawPoint(renderer.get(), p.x, p.y+i);
        }
    }

    // retourne la distance euclidienne à un autre point
    long  double Point::euclideanDistance(Point p){
        long  double dx = this->get_x() - p.get_x();
        long  double dy = this->get_y() - p.get_y();
        return sqrt( dx*dx + dy*dy );
    }
