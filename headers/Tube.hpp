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
    void draw(std::shared_ptr<SDL_Renderer> renderer);
    void clear();
    std::string get_name();
    Tunel get_hall(int index);

protected:
    int width;
    int height;
    std::vector<Tunel> hallList;
    std::string name;
    int nbHall;
    Point center;
    Color color;
    const int thickness = 4;

    
};

#endif