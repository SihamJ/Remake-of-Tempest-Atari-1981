#include "Point.hpp"

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

    std::shared_ptr<SDL_Point> Point::get_point() const {
        std::shared_ptr<SDL_Point> p;
        p.reset( new SDL_Point(this->p));
        return p;
    }

    const bool Point::operator==(const Point&& other)const {
        
        return (this->x == other.get_x() && this->y == other.get_y());
    }

    Point Point::operator-(const Point &other)  {
        return Point(this->x - other.x, this->y - other.y);
    }

    const bool Point::operator!=(const Point &other) const {
        return (this->x != other.get_x() || this->y != other.get_y());
    }

    void Point::set_point (long  double x, long  double y) {
        this->p.x = x;
        this->p.y = y;
        this->x = x;
        this->y = y;
    }

    const long  double Point::get_x()const {
        return this->x;
    }

    const long  double Point::get_y()const {
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
    
    std::array<long  double, 2> Point::cartesian_to_polar(){
        long  double phi, r;

        if(this->x == 0){
            if(this->y == 0)
                return {0, 0};
            // assumption: x and y coordinates are always positive
            phi = 1.5708;
        }
        else
            phi = atan(this->y/this->x);

        r = sqrt(this->x*this->x + this->y*this->y);
        return { phi, r};
    }

    std::array<long  double, 2> Point::polar_to_cartesian(long  double phi, long  double r){
        long  double x, y;
        x = static_cast<int>( r * cos(phi));
        y = static_cast<int>( r * sin(phi));
        return {x, y};
    }


    void Point::draw( std::shared_ptr<SDL_Renderer> renderer) {
        for(int i =0; i<this->thickness; i++){
            SDL_RenderDrawPoint(renderer.get(), p.x+i, p.y);
            SDL_RenderDrawPoint(renderer.get(), p.x+i, p.y+i);
            SDL_RenderDrawPoint(renderer.get(), p.x, p.y+i);
        }
    }

    // retourne la distance euclidienne à un autre point
    const long  double Point::euclideanDistance(Point p)const {
        long  double dx = this->get_x() - p.get_x();
        long  double dy = this->get_y() - p.get_y();
        return sqrt( dx*dx + dy*dy );
    }

    const Point Point::get_point_from_rotation(Point center, double angle) {

        Point p = Point(*this);


        std::array<long double, 2> polar_center = center.cartesian_to_polar();
        std::array<long double, 2> polar_p = p.cartesian_to_polar();

        float phi = polar_p.at(1) + angle;

        std::array<long double, 2> new_p = polar_to_cartesian(phi, polar_p.at(1));

        return Point(new_p.at(0), new_p.at(1));
    }

    void Point::rotate(const Point Pivot, const long double  Angle)
    {
        if (Angle == 0)
            return;

        long double s = sin(Angle);
        long double  c = cos(Angle);

        this->x -= Pivot.get_x();
        this->y -= Pivot.get_y();

        long double  nx = (this->x * c) - (this->y * s);
        long double  ny = (this->x * s) + (this->y * c);

        this->x = nx + Pivot.get_x();
        this->y = ny + Pivot.get_y();
        
    }

    