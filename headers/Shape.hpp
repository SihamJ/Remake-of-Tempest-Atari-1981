#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "Point.hpp"

class Shape {

    public:
        Shape();
        ~Shape();
        virtual void build();

    protected:
        std::vector<Point> points;

};

#endif