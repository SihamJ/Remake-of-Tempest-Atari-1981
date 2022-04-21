#include "../headers/Spikers.hpp"
#include <cmath>

Spikers::Spikers(){}

//constructeur
Spikers::Spikers(std::string name)
{
    this->name = std::move(name);
    this->width = 57;
    this->height = 64;
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
    this->width = 57;
    this->height = 64;
    build();
}

// copy constructor
Spikers::Spikers(const Spikers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Spikers");
    this->width = 57;
    this->height = 64;
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

const int Spikers::get_scoring(){
    return this->scoring;
}

void Spikers::build() {
    // Evalue le random point
    random_p = ((rand() % 725) / 1000.0) + 0.25;
}

bool Spikers::get_closer() {

    Point center_big_line = hall.get_big_line().inLine(0.5);
    Point center_small_line = hall.get_small_line().inLine(0.5);

    Line center_line = Line{center_small_line, center_big_line};

    Point rand_p = center_line.inLine(random_p);

    // avance de 3% // todo avec speed, ptetre un 0.003 * speed 
    double ratio = 0.03;

    SDL_Rect r = {static_cast<int>(x), static_cast<int>(y), 5, 5};

    if (state != 1) {

        // sert à savoir quand le spiker doit s'arrêter
        int x1 = rand_p.get_x() - (center_big_line.get_y() - rand_p.get_y());
        int y1 = rand_p.get_y() - (center_big_line.get_x() - rand_p.get_x());
        int x2 = rand_p.get_x() + (center_big_line.get_y() - rand_p.get_y());
        int y2 = rand_p.get_y() + (center_big_line.get_x() - rand_p.get_x());


        // si le spiker a atteint sa cible
        if (SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2) == SDL_TRUE)
            state = 1;
        
    }


    double init_dist = hall.get_small_line().get_p0().euclideanDistance(hall.get_small_line().get_p1());

    double init_w = init_dist/3.0;
    double init_h = init_dist/3.0;

    // Point centre_small_line = hall.get_small_line().inLine(0.5);

    // double init_x = centre_small_line.get_x() - (init_w/2);
    // double init_y = centre_small_line.get_y() - (init_h/2);

    // Line center_line_test = Line{Point{static_cast<int>(init_x+(init_w/2.0)), static_cast<int>(init_y+(init_h/2.0))}, hall.get_big_line().inLine(0.5)};




    double x1 = center_line.get_p0().get_x();
    double y1 = center_line.get_p0().get_y();
 
    Point coord_vector = center_line.inLine(ratio);

    double x2 = coord_vector.get_x();
    double y2 = coord_vector.get_y();

    double diff_x = x2 - x1;
    double diff_y = y2 - y1;


    // printf("diff_x : %f, diff_y : %f \n", diff_x, diff_y);

    double l1 = hall.get_big_line().get_p0().euclideanDistance(hall.get_big_line().get_p1());
    double l2 = hall.get_small_line().get_p0().euclideanDistance(hall.get_small_line().get_p1());

    double dist = l1 / l2;


    double ajout_w = ((dist * init_w) - init_w) * ratio;
    double ajout_h = ((dist * init_h) - init_h) * ratio;
    
    if (state == 1) {
        this->x -= diff_x;
        this->y -= diff_y;

        ajout_w *= (-1);
        ajout_h *= (-1);
    }
    else {
        this->x += diff_x;
        this->y += diff_y;
    }
    
    this->width += ajout_w;
    this->height += ajout_h;

    this->x -= (ajout_w/2.0);
    this->y -= (ajout_h/2.0);

    angle += 30;

    if (state == 1) {
        int x1 = hall.get_small_line().get_p0().get_x();
        int y1 = hall.get_small_line().get_p0().get_y();
        int x2 = hall.get_small_line().get_p1().get_x();
        int y2 = hall.get_small_line().get_p1().get_y();

        if (SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2) == SDL_TRUE)
            state = 2;
    }

    return false;

    // return intersect(this->hall.get_big_line());
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
    std::string path;
    path = static_cast<std::string>("images/spiker_") + this->get_color().get_name() + static_cast<std::string>(".bmp"); 

    SDL_Surface* image = SDL_LoadBMP(path.c_str());
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

    Point center_small_line = hall.get_small_line().inLine(0.5);

    if (state == 0) {
        SDL_RenderDrawLine(renderer.get(), center_small_line.get_x(), center_small_line.get_y(), x + (width/2.0), y + (height/2.0));
    }
    else {
        Point center_big_line = hall.get_big_line().inLine(0.5);
        Line center_line = Line{center_small_line, center_big_line};

        Point rand_p = center_line.inLine(random_p);

        SDL_RenderDrawLine(renderer.get(), center_small_line.get_x(), center_small_line.get_y(), rand_p.get_x(), rand_p.get_y());
    }
}

    void Spikers::set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect){

        this->center = center;
        this->hall = h;
        this->rect = rect;
        this->start = start;
        this->dest = h.get_big_line().inLine(0.5);

        int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        width = dist/3;
        height = dist/3;

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - (width/2);
        y = centre_small_line.get_y() - (height/2);

        bool cond1 = false;

        double segment_a = centre_big_line.get_x() - centre_small_line.get_x();
        double segment_b = centre_big_line.get_y() - centre_small_line.get_y();
        double segment_c = sqrt(segment_a * segment_a + segment_b * segment_b);
        
        if (segment_a < 0.) {
            segment_a *= -1.;
            cond1 = true;
        }

        angle = acos(segment_a / segment_c) * (180.0/3.141592653589793238463);
        
        if (cond1) {
            angle *= -1.;
        }

        if (segment_b > 0.) {
            if (angle < 0.) {
                angle -= 90.;
            }
            else {
                angle += 90.;
            }
        }
        
    }
