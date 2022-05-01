#include "Pulsars.hpp"

Pulsars::Pulsars(){}

//constructeur
Pulsars::Pulsars(const std::string&& name)
{
    this->name = std::move(name);
}

Pulsars::Pulsars(const std::string&& name, const Color&& c)
    : Enemy(std::move(c))
{
    this->name = std::move(name);
}

//constructeur
Pulsars::Pulsars(const std::string&& name,  const Point&& center,  const Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
}

// copy constructor
Pulsars::Pulsars(const Pulsars &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Pulsars");
}

Pulsars::Pulsars(const Pulsars &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Pulsars");
    this->width = 57;
    this->height = 64;
}

//destructeur
Pulsars::~Pulsars(){}


void Pulsars::set_tunnel(const Tunel& h) { this->hall = h; }


void Pulsars::set_center(const Point& center) { this->center = center; }

void Pulsars::set(Tunel&& h){

        this->hall = h;

        long double dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist/2.;
        this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - ( static_cast<long double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<long double>(height)/2.0);

        this->angle = this->hall.get_angle();
        this->start = this->hall.get_small_line();
        this->dest = this->hall.get_big_line();

    }

void Pulsars::clean(){
    this->lines.clear();
}


bool Pulsars::get_closer(long double h) {

    this->center = Line(this->center, this->hall.get_big_line().inLine(0.5)).inLine(h*h*std::cbrtl(h));
    this->width = 0.8 * h * this->hall.get_big_line().length();
    this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));

    this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
    this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);

    //return false;
    return intersect(this->hall.get_big_line());
}

const bool Pulsars::intersect(Line l) const {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);
}

void Pulsars::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/pulsar_LIGHTBLUE") + static_cast<std::string>(".bmp"); //+ this->color.get_name() + static_cast<std::string>(".bmp"); 

    if(render_image(renderer, path, this->init_width, this->init_height, this->width, this->height, static_cast<const int>(x),  static_cast<const int>(y), 
                    angle, NULL)){
        std::cout << "Can't load pulsar image" <<std::endl;
        return;
    }
}