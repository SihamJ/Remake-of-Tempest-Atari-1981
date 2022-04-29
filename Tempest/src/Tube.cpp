#include "Tube.hpp"

// constructeur
Tube::Tube(){}

Tube::Tube(std::string name, Color c)
    : color(c)
{
    this->name = name;
}

Tube::Tube(std::string&& name, int nbHall, Color&& c)
    : nbHall(nbHall), color(c)
{
    this->name = std::move(name);
}
// destructeur
Tube::~Tube(){}

std::vector<Tunel> Tube::get_hall_list(){
    return hallList;
}

int Tube::get_nb_hall(){
    return this->nbHall;
}

Tunel Tube::get_hall(int index){
    return this->hallList.at( (index + this->get_nb_hall()) % this->get_nb_hall() );
}

Point Tube::get_center(){
    return center;
}

Color Tube::get_color(){
    return this->color;
}

const bool Tube::get_open() const {
    return this->open;
}

void Tube::set_center(Point&& c){
    this->center = c;
}

void Tube::set_nb_hall(int n){
    this->nbHall = n;
}

void Tube::set_open(bool val){
    this->open = val;
}

void Tube::add_Hall (Tunel&& h) {
    hallList.push_back(h);
}

void Tube::delete_hall(){
    
}

void Tube::build_map(){}

void Tube::draw(std::shared_ptr<SDL_Renderer> renderer) {
    for (auto i : hallList) {
        i.draw_shadow(renderer);
    }
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