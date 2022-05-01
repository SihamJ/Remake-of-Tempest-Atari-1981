#ifndef __TUBE_HPP__
#define __TUBE_HPP__

#include <vector>
#include <SDL.h>
#include "Tunel.hpp"


// #include "Shape.hpp"

class Tube {

public:

    Tube();
    Tube(std::string name, Color c);
    Tube(std::string&& name, int nbHall, Color&& c);
    ~Tube();

    std::vector<Tunel> get_hall_list();
    int get_nb_hall();
    Point get_center();
    Color get_color();
    const bool get_open() const;

    void set_center(Point&& c);
    void set_nb_hall(int n);
    void set_open(bool val);
    void add_Hall (Tunel&& h);
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
    const int thickness = 2;

    // vrai si la map est fermée
    bool open = false;
    
};

#endif