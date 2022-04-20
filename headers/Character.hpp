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
    ~Character(){}

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer){
        for (auto i : lines) {
            i.draw(renderer);
        }
    }

    virtual void clean(){
        this->lines.clear();
    }

    virtual void build()=0;

    std::vector<Line> get_lines(){ return this->lines; }
    std::string get_name(){ return this->name; }
    Color get_color(){ return this->color; }

protected:

    std::vector<Line> lines;
    std::string name;
    Color color;
    Tunel hall;
};

#endif