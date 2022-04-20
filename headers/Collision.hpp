#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__

#include "Point.hpp"
#include "Line.hpp"
#include "Color.hpp"

class Collision {
    public:
        Collision();
        Collision(const Point& center);
        Collision(const Point& center, const Color& c, const double& length);
        ~Collision();

        Point get_center();
        Color get_color();
        double get_length();
        void set_center(const Point&& center);
        void set_color(const Color&& color);
        void set_length(const double&& length);

        void build();
        void draw(std::shared_ptr<SDL_Renderer> renderer);

    protected:
        Point center;
        Color color;
        double length;
        std::vector<Line> lines;
};


#endif