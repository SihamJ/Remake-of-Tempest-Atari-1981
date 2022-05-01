#ifndef __SQUARE_MAP_HPP__
#define __SQUARE_MAP_HPP__

#include "Tube.hpp"
#include "Tunel.hpp"
#include "Line.hpp"
#include "Color.hpp"


class SquareMap : public Tube {
    public:
        SquareMap();
        SquareMap(long double ratio, Color&& c);
        ~SquareMap();

        void set_inner_square();
        void set_outer_square();
        void build_map() override;

    private:
        std::vector<Point> inner_square;
        std::vector<Point> outer_square;
        long double ratio;

};

#endif