#include "../headers/Tube.hpp"

// constructeur
Tube::Tube(){}

Tube::Tube(const char* name, const int nbHall, const Color c)
    : nbHall(nbHall), color(c)
{
    this->name = static_cast<std::string>(name);
}
// destructeur
Tube::~Tube(){}

std::vector<Tunel> Tube::get_hall_list(){
    return hallList;
}

int Tube::get_nb_hall(){
    return this->nbHall;
}

Point Tube::get_center(){
    return center;
}

Color Tube::get_color(){
    return this->color;
}

void Tube::set_center(const Point c){
    this->center = c;
}

void Tube::set_nb_hall(const int n){
    this->nbHall = n;
}


void Tube::add_Hall (const Tunel h) {
    hallList.push_back(h);
}

void Tube::delete_hall(){
    
}

void Tube::build_map(){}

void Tube::draw(SDL_Renderer* renderer) {
    for (auto i : hallList) {
        i.draw(renderer);
    }
}
void Tube::clear(){
    hallList.clear();
}

std::string Tube::get_name(){
    return this->name;
}