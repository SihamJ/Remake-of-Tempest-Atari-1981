#include "../headers/Point.hpp"

    Point::Point(){}

    Point::Point(double x, double y){
        this->x = x;
        this->y = y;
    }

    Point::Point(float phi, float r){
        this->phi = phi;
        this->r = r;
    }

    Point::Point(int x, int y, float phi, float r){
        this->x = x;
        this->y = y;
        this->phi = phi;
        this->r = r;
    }

    Point::Point(std::array<double, 2> point){
        p = point;
    }

    Point::Point(const Point &other)
        : x(other.x), y(other.y), phi(other.phi), r(other.r), p(other.p), dest(other.dest)
    {

    }


    // Destructeur
    Point::~Point(){}

    /**
     * @brief Set the point object
     * 
     * @param x 
     * @param y 
     */
    void Point::set_point (double x, double y) {
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Get the point object
     * 
     * @return std::array<int, 2> 
     */
    std::array<double, 2> Point::get_point () {
        return {this->x, this->y};
    }

    double Point::get_x(){
        return this->x;
    }

    double Point::get_y(){
        return this->y;
    }

    void Point::set_polar(float phi, float r){
        this->phi = phi;
        this->r = r;
    }

    void Point::set_cartesian(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    std::array<float, 2> Point::cartesian_to_polar(int x, int y){
        float phi, r;
        float xx = static_cast<float>(x);
        float yy = static_cast<float>(y);

        if(x == 0){
            if(y == 0)
                return {0, 0};
            // assumption: x and y coordinates are always positive
            phi = 1.5708;
        }
        else
            phi = atan(yy/xx);

        r = sqrt(xx*xx + yy*yy);
        return { phi, r};
    }

    std::array<int, 2> Point::polar_to_cartesian(float phi, float r){
        int x, y;
        x = static_cast<int>( r * cos(phi));
        y = static_cast<int>( r * sin(phi));
        return {x, y};
    }

    /**
     * @brief Dessine le point
     * 
     * @param renderer 
     */
    void Point::draw( std::shared_ptr<SDL_Renderer> renderer) {
        SDL_RenderDrawPoint(renderer.get(), this->x, this->y);
    }

    /**
     * @brief Set the dest object
     * 
     * @param dest 
     */
    void Point::set_dest (std::array<double, 2> destination) {
        dest = destination;
    }

    /**
     * @brief Get the dest object
     * 
     * @return std::array<int, 2> 
     */
    std::array<double, 2> Point::get_dest () {
        return dest;
    }

    /**
     * @brief Rapproche le point de la destination 
     * (+ ou - en fct de la variable "vitesse")
     *  
     * @return vrai si on a atteint l'objectif (= doit être détruit)
     */
    bool Point::get_closer() {
        int diff_x = dest[0] - this->x;
        int diff_y = dest[1] - this->y;
        int coeff_x = (diff_x > 0) ? 1 : -1;
        int coeff_y = (diff_y > 0) ? 1 : -1;
        if (diff_x != 0 || diff_y != 0) {
            this->x += speed * diff_x / (coeff_x * diff_x + coeff_y * diff_y);
            this->y += speed * diff_y / (coeff_x * diff_x + coeff_y * diff_y);
        }
        int nv_coeff_x = ((dest[0] - this->x) > 0) ? 1 : -1;
        int nv_coeff_y = ((dest[1] - this->y) > 0) ? 1 : -1;

        // Si ça dépasse le centre, les points sont "détruits"
        if ((nv_coeff_x != coeff_x) || (nv_coeff_y != coeff_y) || (p == dest)) {
            return true;
        }
        return false;
    }

    // retourne la distance euclidienne à un autre point
    double Point::euclideanDistance(Point p){
        double dx = (double) abs(this->get_x() - p.get_x());
        double dy = (double) abs(this->get_y() - p.get_y());
        return sqrt( dx*dx + dy*dy );
    }
