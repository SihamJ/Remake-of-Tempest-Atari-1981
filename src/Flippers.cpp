#include "../headers/Flippers.hpp"

Flippers::Flippers(){}

//constructeur
Flippers::Flippers(std::string name)
{
    this->name = std::move(name);
}

Flippers::Flippers(std::string  name, Color& c)
    : Enemy(c)
{
    this->name = name;
}

//constructeur
Flippers::Flippers(std::string name, const Point& center, const Tunel& h, const std::array<Point, 4> &rect)
    : Enemy(center, h, rect)
{
    this->name = std::move(name);
    build();
}

// copy constructor
Flippers::Flippers(const Flippers &other) 
    : Enemy(other)
{ 
     this->name = static_cast<std::string>("Flippers");
    build();
}

//destructeur
Flippers::~Flippers(){}



void Flippers::set_dest (const Point& destination){
    this->dest = destination;
}

void Flippers::set_tunnel(const Tunel& h){
    this->hall = h;
}

void Flippers::set_rect(const std::array<Point, 4> rect){
    this->rect = rect;
}

void Flippers::set_center(const Point& center){
    this->center = center;
}

void Flippers::build() {
    // std::cout << "Flippers build" << std::endl;
    //line 1
    Point p0, p1, p2, p3, p4, p5;
    std::array<Line, 6> l;
    
    p0 = rect.at(0);
    p1 = rect.at(2);
    p3 = rect.at(1);
    p4 = rect.at(3);

    Line l2 = Line(p1, p3);
    Point p = l2.inLine(0.5);
    Line l3 = Line(center, p);
    p2 = l3.inLine(0.5);

    l2.set_line(p0, p4);
    p = l2.inLine(0.5);
    l3 = Line(center, p);
    p5 = l3.inLine(0.5);


    l[0] = Line(p0, p1);
    l[1] = Line(p1, p2);
    l[2] = Line(p2, p3);
    l[3] = Line(p3, p4);
    l[4] = Line(p4, p5);
    l[5] = Line(p5, p0);

    for(auto i : l){
        this->lines.push_back(i);
    }

}

void Flippers::clean(){
    this->lines.clear();
}



/**
 * @brief Rapproche le point de la destination 
 * (+ ou - en fct de la variable "vitesse")
 *  
 * @return vrai si on a atteint l'objectif (= doit être détruit)
 */
bool Flippers::get_closer() {

    double h0 = 0.03;
    double ratio;
    double z = this->center.euclideanDistance(this->dest);
    double d = this->start.euclideanDistance(this->dest);

    ratio = 1 - ( (1-h0) / (d*d) ) * (z*z);
    this->center = Line(this->start, this->dest).inLine(ratio);


    Line l1, l2, l3, l4;
    l1 = Line(rect.at(0), hall.get_big_line().get_p0());
    l2 = Line(rect.at(1), hall.get_big_line().get_p1());
    l3 = Line(rect.at(2), hall.get_big_line().get_p1());
    l4 = Line(rect.at(3), hall.get_big_line().get_p0());

    

    this->rect.at(0) = l1.inLine(ratio);
    this->rect.at(1) = l2.inLine(ratio);
    this->rect.at(2) = l3.inLine(ratio);
    this->rect.at(3) = l4.inLine(ratio);


    this->clean();
    this->build();

    return intersect(this->hall.get_big_line());
}

bool Flippers::intersect(Line l) {
    SDL_Rect r;
    r.w = (int) rect.at(0).euclideanDistance(rect.at(1));
    r.h = (int) rect.at(1).euclideanDistance(rect.at(2));
    r.x = center.get_x();
    r.y = center.get_y();

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

}

