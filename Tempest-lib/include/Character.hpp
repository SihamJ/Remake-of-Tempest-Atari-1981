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

    Character(Character&& other)
        : name(std::move(other.name)), hall(std::move(other.hall)), color(std::move(other.color)), lines(std::move(other.lines))
    {
    }

    ~Character(){}


    std::vector<Line> get_lines() const { return this->lines; }
    virtual const std::string get_name() const  { return this->name; }
    Tunel get_hall() const { return this->hall; }
    Color get_color() const { return this->color; }
    const int get_n_hall() const { return this->hall.get_n_hall(); }

    void set_hall(const Tunel& hall){ this->hall = hall; }

    // dessines le character
    virtual void draw(std::shared_ptr<SDL_Renderer> renderer)= 0;

    // clear les dessins du character
    virtual void clean(){ this->lines.clear(); }
    
    

protected:
    // les lignes qui permettent de dessiner le character
    std::vector<Line> lines;
    // nom de l'ennemi ou personnage
    std::string name;
    // Couleur du character
    Color color;
    // Tunnel où se trouve le character
    Tunel hall;
};

#endif