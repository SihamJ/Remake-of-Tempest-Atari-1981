#include "../headers/Spikers.hpp"
#include <cmath>

Spikers::Spikers(){}

//constructeur
Spikers::Spikers(std::string name)
{
    this->name = std::move(name);
}

Spikers::Spikers(std::string  name, Color& c)
    : Spikers(name) 
{
    this->color = c;
}

//constructeur
Spikers::Spikers(std::string name, const Point& center, const Tunel& h, const std::array<Point, 4> &rect)
    : Enemy(center, h, rect)
{
    this->name = std::move(name);
    build();
}

// copy constructor
Spikers::Spikers(const Spikers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Spikers");
    build();
}

//destructeur
Spikers::~Spikers(){}



void Spikers::set_dest (const Point& destination){
    this->dest = destination;
}

void Spikers::set_tunnel(const Tunel& h){
    this->hall = h;
}

void Spikers::set_rect(const std::array<Point, 4> rect){
    this->rect = rect;
}

void Spikers::set_center(const Point& center){
    this->center = center;
}

void Spikers::build() {
    // std::cout << "Spikers build" << std::endl;
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

    // p2.set_point(p1.get_x() -  ,center.get_y());

    l[0] = Line(p0, p1);

    // p3.set_point(center.get_x() + 5*(wx - center.get_x())/3 , center.get_y() - ch.get_y()/2);
    l[1] = Line(p1, p2);

    // p4.set_point(p2.get_x(), p2.get_y() + 2*ch.get_y()/3);
    l[2] = Line(p2, p3);

    // p5.set_point(p1.get_x(), p1.get_y() - 2*ch.get_y()/3);
    l[3] = Line(p3, p4);

    // p6.set_point(wx - 5*(wx - center.get_x())/3 , center.get_y() - ch.get_y()/2);
    l[4] = Line(p4, p5);

    l[5] = Line(p5, p0);

    for(auto i : l){
        this->lines.push_back(i);
    }

}

void Spikers::clean(){
    this->lines.clear();
}



/**
 * @brief Rapproche le point de la destination 
 * (+ ou - en fct de la variable "vitesse")
 *  
 * @return vrai si on a atteint l'objectif (= doit être détruit)
 */
bool Spikers::get_closer() {
    // avance de 3% // todo avec speed, ptetre un 0.003 * speed 
    double ratio = 0.03;

    double init_dist = hall.get_small_line().get_p0().euclideanDistance(hall.get_small_line().get_p1());

    double init_w = init_dist/3.0;
    double init_h = init_dist/3.0;

    // Point centre_small_line = hall.get_small_line().inLine(0.5);

    // double init_x = centre_small_line.get_x() - (init_w/2);
    // double init_y = centre_small_line.get_y() - (init_h/2);

    // Line center_line_test = Line{Point{static_cast<int>(init_x+(init_w/2.0)), static_cast<int>(init_y+(init_h/2.0))}, hall.get_big_line().inLine(0.5)};



    Line center_line = Line{hall.get_small_line().inLine(0.5), hall.get_big_line().inLine(0.5)};

    double x1 = center_line.get_p0().get_x();
    double y1 = center_line.get_p0().get_y();
 
    Point coord_vector = center_line.inLine(ratio);

    double x2 = coord_vector.get_x();
    double y2 = coord_vector.get_y();

    double diff_x = x2 - x1;
    double diff_y = y2 - y1;

    this->x += diff_x;
    this->y += diff_y;

    double l1 = hall.get_big_line().get_p0().euclideanDistance(hall.get_big_line().get_p1());
    double l2 = hall.get_small_line().get_p0().euclideanDistance(hall.get_small_line().get_p1());

    double dist = l1 / l2;

    

    double ajout_w = (((dist * init_w) - init_w) * ratio);
    double ajout_h = (((dist * init_h) - init_h) * ratio);

    this->width += ajout_w;
    this->height += ajout_h;

    this->x -= (ajout_w/2.0);
    this->y -= (ajout_h/2.0);

    angle += 30;

    return intersect(this->hall.get_big_line());
}

bool Spikers::intersect(Line l) {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

}

void Spikers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    SDL_Surface* image = SDL_LoadBMP("images/spiker.bmp");
    if(!image)
    {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    // dessiner le spiker
    SDL_Rect dest_rect = {static_cast<int>(x), static_cast<int>(y), init_width, init_height};
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer.get(), image);  //La texture monImage contient maintenant l'image importée
    SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface

    if (SDL_QueryTexture(monImage, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    dest_rect.w = width;
    dest_rect.h = height;

    if (SDL_RenderCopyEx(renderer.get(), monImage, NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }
}