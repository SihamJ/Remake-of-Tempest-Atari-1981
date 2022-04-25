#include "../headers/CircleMap.hpp"

    CircleMap::CircleMap(){}

    CircleMap::CircleMap(const long double ratio, const Color& c)
        : Tube("Circle", c), ratio(ratio)
    {
        this->width = 3 * WIDTH / 8;
        this->height = 4 * HEIGHT / 5;
        this->center = Point(WIDTH/2., HEIGHT * (1-ratio));
        this->nbHall = 16;
    }

    CircleMap::~CircleMap(){}

    void CircleMap::set_inner_circle(){
        long double inner_height = static_cast<long double>(this->height) / 6.;
        long double inner_width = static_cast<long double>(this->width) / 6.;
        long double upper_y_step = inner_height*(1-this->ratio) / 20.;

        Point p0 { this->center.get_x(), this->center.get_y() +  inner_height*this->ratio };
        Point p3 { this->center.get_x() + inner_width / 2 , this->center.get_y() - 0.5 * upper_y_step };
        Point p2 { p3.get_x() - (p3.get_x() - p0.get_x())/3, p0.get_y() - (p0.get_y() - center.get_y())/2 };
        Point p1 { p0.get_x() + (p3.get_x() - p0.get_x())/3, p0.get_y() - (p0.get_y() - center.get_y())/8 };
        Point p5 { p3.get_x() - inner_width / 23., this->center.get_y()- 11 * upper_y_step };
        Point p6 { p2.get_x(), this->center.get_y() - 15 * upper_y_step};
        Point p7 { p1.get_x(), this->center.get_y() - 18 * upper_y_step};
        Point p4 { p3.get_x() + inner_width / 40., this->center.get_y() - 6 * upper_y_step};

        Point p8 { this->center.get_x(), this->center.get_y() - 19*upper_y_step};
        Point p13 { this->center.get_x() - inner_width / 2 , p3.get_y()};
        Point p14 { p13.get_x() + (p0.get_x() - p13.get_x())/3, p2.get_y() };
        Point p15 { p0.get_x() - (p0.get_x()-p13.get_x())/3, p1.get_y()};
        Point p11 { p13.get_x() + inner_width / 23., p5.get_y()};
        Point p10 { p14.get_x(), p6.get_y()};
        Point p9 { p15.get_x(), p7.get_y()};
        Point p12 { p13.get_x() - inner_width/40., p4.get_y()}; 

        inner_circle.push_back(p0);
        inner_circle.push_back(p1);
        inner_circle.push_back(p2);
        inner_circle.push_back(p3);
        inner_circle.push_back(p4);
        inner_circle.push_back(p5);
        inner_circle.push_back(p6);
        inner_circle.push_back(p7);
        inner_circle.push_back(p8);
        inner_circle.push_back(p9);
        inner_circle.push_back(p10);
        inner_circle.push_back(p11);
        inner_circle.push_back(p12);
        inner_circle.push_back(p13);
        inner_circle.push_back(p14);
        inner_circle.push_back(p15);
        inner_circle.push_back(p0);
    }

    void CircleMap::set_outer_circle(){

        long double upper_y_step = static_cast<long double>(this->height)*(1. - this->ratio) / 20.;
        long double height = static_cast<long double>(this->height);
        long double width = static_cast<long double>(this->width);

        Point p0 { this->center.get_x(), this->center.get_y() +  height*this->ratio };
        Point p3 { this->center.get_x() + width / 2 , this->center.get_y() - 0.5*upper_y_step };
        Point p2 { p3.get_x() - (p3.get_x() - p0.get_x())/3, p0.get_y() - (p0.get_y() - center.get_y())/2 };
        Point p1 { p0.get_x() + (p3.get_x() - p0.get_x())/3, p0.get_y() - (p0.get_y() - center.get_y())/8 };
        Point p5 { p3.get_x() - width / 23., this->center.get_y() - 11 * upper_y_step };
        Point p6 { p2.get_x(), this->center.get_y() - 15 * upper_y_step};
        Point p7 { p1.get_x(), this->center.get_y() - 18 * upper_y_step};
        Point p4 { p3.get_x() + width / 40., center.get_y() - 6 * upper_y_step};

        Point p8 { this->center.get_x(), this->center.get_y() - 19*upper_y_step};
        Point p13 { this->center.get_x() - width / 2 , p3.get_y()};
        Point p14 { p13.get_x() + (p0.get_x() - p13.get_x())/3, p2.get_y() };
        Point p15 { p0.get_x() - (p0.get_x() - p13.get_x())/3, p1.get_y()};
        Point p11 { p13.get_x() + width / 23., p5.get_y()};
        Point p10 { p14.get_x(), p6.get_y()};
        Point p9 { p15.get_x(), p7.get_y()};
        Point p12 { p13.get_x() - width/40., p4.get_y()}; 

        outer_circle.push_back(p0);
        outer_circle.push_back(p1);
        outer_circle.push_back(p2);
        outer_circle.push_back(p3);
        outer_circle.push_back(p4);
        outer_circle.push_back(p5);
        outer_circle.push_back(p6);
        outer_circle.push_back(p7);
        outer_circle.push_back(p8);
        outer_circle.push_back(p9);
        outer_circle.push_back(p10);
        outer_circle.push_back(p11);
        outer_circle.push_back(p12);
        outer_circle.push_back(p13);
        outer_circle.push_back(p14);
        outer_circle.push_back(p15);
        outer_circle.push_back(p0);
    }

    void CircleMap::build_map(){
        set_inner_circle();
        set_outer_circle();

        for(int i = 0; i <= 16; i++){
            Tunel h = Tunel(outer_circle.at(i), outer_circle.at((i+1)%outer_circle.size()), 
                                            inner_circle.at(i), inner_circle.at((i+1)%inner_circle.size()), 2);
            h.set_angle();
            h.set_nb_hall(i);
            this->add_Hall(h);
        }

    }