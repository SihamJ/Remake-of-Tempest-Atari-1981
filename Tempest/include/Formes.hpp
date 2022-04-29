#ifndef __FORMES_HPP__
#define __FORMES_HPP__

#include <SDL.h>

extern int WIDTH;
extern int HEIGHT;

class Formes {

public:

    //constructeur
    Formes(){}
    //destructeur
    ~Formes(){}

    virtual void draw(std::shared_ptr<SDL_Renderer> renderer) = 0;


};


#endif