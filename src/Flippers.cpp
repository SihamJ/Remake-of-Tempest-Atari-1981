#include "../headers/Flippers.hpp"

#define RATIO_RANDOM_P 0.75

Flippers::Flippers(){}

//constructeur
Flippers::Flippers(std::string&& name)
{
    this->name = std::move(name);
}

Flippers::Flippers(std::string&& name, Color&& c)
    : Enemy(std::move(c))
{
    this->name = std::move(name);
}

//constructeur
Flippers::Flippers(std::string&& name,  Point&& center,  Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
}

// copy constructor
Flippers::Flippers(const Flippers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Flippers");
}

Flippers::Flippers(Flippers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Flippers");
    this->width = 57;
    this->height = 64;
}

//destructeur
Flippers::~Flippers(){}


void Flippers::set_tunnel(const Tunel& h) { this->hall = h; }


void Flippers::set_center(const Point& center) { this->center = center; }

void Flippers::set_next_hall(Tunel &&h){
    this->next_hall = h;
}

void Flippers::set_current_angle(double angle){
    this->current_angle = angle;
}

void Flippers::set_flipping(bool flipping){
    this->isFlipping = flipping;
}

const long double Flippers::get_speed() const {
    return this->speed;
}

const Tunel Flippers::get_next_hall() const {
    return this->next_hall;
}

const double Flippers::get_current_angle() const{
    return this->current_angle;
}

const int Flippers::get_state() const {
    return this->state;
}

const bool Flippers::flipping() const{
    return this->isFlipping;
}

void Flippers::set(Tunel&& h){

        this->hall = h;

        double dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist;
        this->height = static_cast<double>(init_height) * ( static_cast<double>(width) / static_cast<double>(init_width));

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - ( static_cast<double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<double>(height)/2.0);

        this->angle = this->hall.get_angle();
        this->start = this->hall.get_small_line();

        this->random_p = RATIO_RANDOM_P; //rand(gen);
        this->hall = h;
        this->state = 0;

        // On calcule la ligne limit de déplacement du spiker (parallèle à big line)
        Point sp0 = this->hall.get_small_line().get_p0();
        Point sp1 = this->hall.get_small_line().get_p1();
        Point bp0 = this->hall.get_big_line().get_p0();
        Point bp1 = this->hall.get_big_line().get_p1();

        long double segment1 = this->random_p * (sp0.euclideanDistance(bp0));
        long double segment2 = this->random_p * (sp1.euclideanDistance(bp1));
        Line l1 = Line(sp0, bp0);
        Line l2 = Line(sp1, bp1);

        Point pp0 = l1.inLine(segment1 / l1.length());
        Point pp1 = l2.inLine(segment2 / l2.length());

        this->limit_init.set_points({pp0, pp1});
        this->dest = Line(limit_init);

    }


bool Flippers::get_closer(long double h) {

    Point c = hall.get_small_line().inLine(0.5);

    if(this->state == 0 && this->center == this->limit_init.inLine(0.5))
    {
        std::cout << "from 0 to 1 " <<std::endl;
        this->state = 1;
        this->isFlipping = false;
        this->current_angle = this->angle;
    }

    else if(this->state == 1 && !this->isFlipping){
        this->isFlipping = true;
    }

    else if(this->state == 1 && this->isFlipping){
        if(this->current_angle >= this->next_angle){
            this->isFlipping = false;
            this->hall = Tunel(this->next_hall);
            this->state = 0;
        }
        else
            this->current_angle += this->next_angle / this->flip_steps;
    }

    if(this->state == 0) {
        this->center = Line(this->center, this->dest.inLine(0.5)).inLine(h*h*std::cbrtl(h));
        this->width = 0.8 * h * this->hall.get_big_line().length();
        this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
    }

    else if(this->state == 1 && this->isFlipping){
        this->center = Point(this->x, this->y).get_point_from_rotation(this->center, this->current_angle);
    }

    return false;
    //return intersect(this->hall.get_big_line());
}

bool Flippers::intersect(Line l) {

    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y + height/2.), static_cast<int>(this->x + this->width), static_cast<int>(this->y + this->height/2.)};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);
}

void Flippers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/flipper_") + this->color.get_name() + static_cast<std::string>(".bmp"); 
    double angle = 0.;
    auto image = (sdl_shared(SDL_LoadBMP(path.c_str())));

    if(!image)
    {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    // dessiner le spiker
    SDL_Rect dest_rect = {static_cast<int>(x), static_cast<int>(y), init_width, init_height};

    auto monImage = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));
   
    if (SDL_QueryTexture(monImage.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    Point center;

    if(this->state == 0){
        angle = this->angle;
        center.set_point(width/2., height/2.);
    }
    else if(this->state == 1 && this->isFlipping){
        angle = this->current_angle;
        center.set_point(this->x, this->y);
    }
    else if(this->state == 1 && !this->isFlipping){
        angle = this->angle;
        center.set_point(width/2., height/2.);
    }

    dest_rect.w = width;
    dest_rect.h = height;

    if (SDL_RenderCopyEx(renderer.get(), monImage.get(), NULL, &dest_rect, angle, center.get_point().get(), SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }
}