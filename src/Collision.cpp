#include "../headers/Collision.hpp"

    Collision::Collision(){}

    Collision::Collision(const Point& center)
        : center(center)
    {
    }

    Collision::Collision(const Point& center, const Color& c, const double& length)
        : center(center), color(c), length(length)
    {
    }

    Collision::~Collision(){};

    Point Collision::get_center(){
        return this->center;
    }

    Color Collision::get_color(){
        return this->color;
    }

    void Collision::set_center(const Point&& center){
        this->center = center;
    }

    void Collision::set_color(const Color&& color){
        this->color = color;
    }

    void Collision::build(){
        // Eq Cercle : (x−a)² + (y−b)² = r²   || (a,b) =  center

        std::vector<Point> points;
        float y_max = this->center.get_y() + this->length/2.0;
        float y_min = this->center.get_y() - this->length/2.0;
        float y_step = (y_max - y_min) / 8.0;
        
        float y = y_min;
        float x;

        for (int i = 0; i < 4; i++){
            x = sqrt(this->length*this->length - (y - this->center.get_y())*(y - this->center.get_y())) + this->center.get_x();
            points.push_back(Point(x, y));
            y += y_step;
        }

        y -= y_step;

        for (int i = 0; i < 4; i++){
            x = sqrt(this->length*this->length - (y - this->center.get_y())*(y - this->center.get_y())) + this->center.get_x();
            points.push_back(Point(x, y));
            y -= y_step ;
        }

        for (auto i : points){
            this->lines.push_back(Line(this->center, i));
        }

    }

    void Collision::draw(std::shared_ptr<SDL_Renderer> renderer){
        std::cout << "Drawing collision" << std::endl;
        for (auto i : lines){
            i.draw(renderer);
        }
    }