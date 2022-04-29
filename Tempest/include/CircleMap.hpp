#ifndef __CIRCLE_MAP_HPP__
#define __CIRCLE_MAP_HPP__

#include "Point.hpp"
#include "Line.hpp"
#include "Color.hpp"
#include "Utils.hpp"
#include "Tube.hpp"
#include <vector>


class CircleMap : public Tube {
    public:
        
        CircleMap();
        CircleMap(const long double ratio, Color&& c);
        ~CircleMap();

        void build_map() override;
        void set_inner_circle();
        void set_outer_circle();

    private:
        std::vector<Point> inner_circle;
        std::vector<Point> outer_circle;
        long double ratio;
};



#endif