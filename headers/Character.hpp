#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <vector>
#include <string>
#include "Line.hpp"

class Character {

public:

    Character(){}
    ~Character(){}

    virtual void draw(SDL_Renderer* renderer){
        for (auto i : lines) {
            i.draw(renderer);
        }
    }

private:
    std::vector<Line> lines;
    std::string name;
};

#endif