#ifndef __TUBE_HPP__
#define __TUBE_HPP__

#include <vector>
#include <SDL.h>
#include "Tunel.hpp"

// #include "Shape.hpp"

class Tube {

public:

    Tube();
    Tube(const char* name, const int nbHall, const Color c);
    ~Tube();

    std::vector<Tunel> get_hall_list();
    int get_nb_hall();
    Point get_center();
    Color get_color();
    void set_center(const Point c);
    void set_nb_hall(const int n);
    void add_Hall (const Tunel h);
    void delete_hall();
    virtual void build_map();
    void draw(SDL_Renderer* renderer);
    void clear();
    std::string get_name();

protected:
    int width;
    int height;
    std::vector<Tunel> hallList;
    std::string name;
    int nbHall;
    Point center;
    Color color;
    // Shape inner_shape;
    // Shape outer_shape;
    
};

#endif