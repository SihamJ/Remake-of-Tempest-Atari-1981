#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <vector>
#include <string>
#include "Line.hpp"
#include "Color.hpp"
#include "Tunel.hpp"

class Character {

public:

    Character(){}

    Character(const Character& other)
        : name(other.name), hall(other.hall), color(other.color), lines(other.lines)
    {
    }

    Character(const Character&& other)
        : name(std::move(other.name)), hall(std::move(other.hall)), color(std::move(other.color)), lines(std::move(other.lines))
    {
    }

    ~Character(){}

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer)= 0;

    virtual void clean(){
        this->lines.clear();
    }

    std::vector<Line> get_lines() const { return this->lines; }
    virtual const std::string get_name() const  { return this->name; }
    Tunel get_hall() const { return this->hall; }
    Color get_color() const { return this->color; }
    int get_n_hall(){ return this->hall.get_n_hall(); }

    void set_hall(const Tunel& hall){
        this->hall = hall;
    }
    

protected:

    std::vector<Line> lines;
    std::string name;
    Color color;
    Tunel hall;
};

#endif