#ifndef __FORMES_HPP__
#define __FORMES_HPP__

#include <SDL.h>

class Formes {

public:

    //constructeur
    Formes(){}
    //destructeur
    ~Formes(){}

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer) = 0;


};


#endif