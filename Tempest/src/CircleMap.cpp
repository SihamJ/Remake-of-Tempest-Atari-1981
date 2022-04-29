#include "CircleMap.hpp"

    extern int WIDTH;
    extern int HEIGHT;

    CircleMap::CircleMap(){}

    CircleMap::CircleMap(const long double ratio, Color&& c)
        : Tube("Circle", std::move(c)), ratio(ratio)
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

        Point p0 { std::move(this->center.get_x()), std::move(this->center.get_y() +  inner_height*this->ratio) };
        Point p3 { std::move(this->center.get_x() + inner_width / 2) , std::move(this->center.get_y() - 0.5*upper_y_step) };
        Point p2 { std::move(p3.get_x() - (p3.get_x() - p0.get_x())/3), std::move(p0.get_y() - (p0.get_y() - center.get_y())/2) };
        Point p1 { std::move(p0.get_x() + (p3.get_x() - p0.get_x())/3), std::move(p0.get_y() - (p0.get_y() - center.get_y())/8) };
        Point p5 { std::move(p3.get_x() - inner_width / 23.), std::move(this->center.get_y() - 11 * upper_y_step )};
        Point p6 { std::move(p2.get_x()), std::move(this->center.get_y() - 15 * upper_y_step)};
        Point p7 { std::move(p1.get_x()), std::move(this->center.get_y() - 18 * upper_y_step)};
        Point p4 { std::move(p3.get_x() + inner_width / 40.), std::move(center.get_y() - 6 * upper_y_step)};

        Point p8 { std::move(this->center.get_x()), std::move(this->center.get_y() - 19*upper_y_step)};
        Point p13 { std::move(this->center.get_x() - inner_width / 2) , std::move(p3.get_y())};
        Point p14 { std::move(p13.get_x() + (p0.get_x() - p13.get_x())/3), std::move(p2.get_y()) };
        Point p15 { std::move(p0.get_x() - (p0.get_x() - p13.get_x())/3), std::move(p1.get_y())};
        Point p11 { std::move(p13.get_x() + inner_width / 23.), std::move(p5.get_y())};
        Point p10 { std::move(p14.get_x()), std::move(p6.get_y())};
        Point p9 { std::move(p15.get_x()), std::move(p7.get_y())};
        Point p12 { std::move(p13.get_x() - inner_width/40.), std::move(p4.get_y())}; 

        inner_circle.push_back(std::move(p0));
        inner_circle.push_back(std::move(p1));
        inner_circle.push_back(std::move(p2));
        inner_circle.push_back(std::move(p3));
        inner_circle.push_back(std::move(p4));
        inner_circle.push_back(std::move(p5));
        inner_circle.push_back(std::move(p6));
        inner_circle.push_back(std::move(p7));
        inner_circle.push_back(std::move(p8));
        inner_circle.push_back(std::move(p9));
        inner_circle.push_back(std::move(p10));
        inner_circle.push_back(std::move(p11));
        inner_circle.push_back(std::move(p12));
        inner_circle.push_back(std::move(p13));
        inner_circle.push_back(std::move(p14));
        inner_circle.push_back(std::move(p15));
        inner_circle.push_back(std::move(p0));
    }

    void CircleMap::set_outer_circle(){

        long double upper_y_step = static_cast<long double>(this->height)*(1. - this->ratio) / 20.;
        long double height = static_cast<long double>(this->height);
        long double width = static_cast<long double>(this->width);

        Point p0 { std::move(this->center.get_x()), std::move(this->center.get_y() +  height*this->ratio) };
        Point p3 { std::move(this->center.get_x() + width / 2) , std::move(this->center.get_y() - 0.5*upper_y_step) };
        Point p2 { std::move(p3.get_x() - (p3.get_x() - p0.get_x())/3), std::move(p0.get_y() - (p0.get_y() - center.get_y())/2) };
        Point p1 { std::move(p0.get_x() + (p3.get_x() - p0.get_x())/3), std::move(p0.get_y() - (p0.get_y() - center.get_y())/8) };
        Point p5 { std::move(p3.get_x() - width / 23.), std::move(this->center.get_y() - 11 * upper_y_step )};
        Point p6 { std::move(p2.get_x()), std::move(this->center.get_y() - 15 * upper_y_step)};
        Point p7 { std::move(p1.get_x()), std::move(this->center.get_y() - 18 * upper_y_step)};
        Point p4 { std::move(p3.get_x() + width / 40.), std::move(center.get_y() - 6 * upper_y_step)};

        Point p8 { std::move(this->center.get_x()), std::move(this->center.get_y() - 19*upper_y_step)};
        Point p13 { std::move(this->center.get_x() - width / 2) , std::move(p3.get_y())};
        Point p14 { std::move(p13.get_x() + (p0.get_x() - p13.get_x())/3), std::move(p2.get_y()) };
        Point p15 { std::move(p0.get_x() - (p0.get_x() - p13.get_x())/3), std::move(p1.get_y())};
        Point p11 { std::move(p13.get_x() + width / 23.), std::move(p5.get_y())};
        Point p10 { std::move(p14.get_x()), std::move(p6.get_y())};
        Point p9 { std::move(p15.get_x()), std::move(p7.get_y())};
        Point p12 { std::move(p13.get_x() - width/40.), std::move(p4.get_y())}; 

        outer_circle.push_back(std::move(p0));
        outer_circle.push_back(std::move(p1));
        outer_circle.push_back(std::move(p2));
        outer_circle.push_back(std::move(p3));
        outer_circle.push_back(std::move(p4));
        outer_circle.push_back(std::move(p5));
        outer_circle.push_back(std::move(p6));
        outer_circle.push_back(std::move(p7));
        outer_circle.push_back(std::move(p8));
        outer_circle.push_back(std::move(p9));
        outer_circle.push_back(std::move(p10));
        outer_circle.push_back(std::move(p11));
        outer_circle.push_back(std::move(p12));
        outer_circle.push_back(std::move(p13));
        outer_circle.push_back(std::move(p14));
        outer_circle.push_back(std::move(p15));
        outer_circle.push_back(std::move(p0));
    }

    void CircleMap::build_map(){

        this->set_inner_circle();
        this->set_outer_circle();

        for(int i = 0; i <= 16; i++){
            Tunel h = Tunel(std::move(outer_circle.at(i)), std::move(outer_circle.at((i+1)%outer_circle.size())), 
                                            std::move(inner_circle.at(i)), std::move(inner_circle.at((i+1)%inner_circle.size())), 2);
            h.set_angle();
            h.set_nb_hall(i);
            this->add_Hall(std::move(h));
        }

    }