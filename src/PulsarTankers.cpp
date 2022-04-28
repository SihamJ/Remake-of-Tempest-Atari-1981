#include "../headers/PulsarTankers.hpp"

PulsarTankers::PulsarTankers(){}

//constructeur
PulsarTankers::PulsarTankers(std::string&& name)
{
    this->name = std::move(name);
}

PulsarTankers::PulsarTankers(std::string&& name, Color&& c)
    : Enemy(std::move(c))
{
    this->name = std::move(name);
}

//constructeur
PulsarTankers::PulsarTankers(std::string&& name,  Point&& center,  Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
}

// copy constructor
PulsarTankers::PulsarTankers(const PulsarTankers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("PulsarTankers");
}

PulsarTankers::PulsarTankers(PulsarTankers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("PulsarTankers");
    this->width = 57;
    this->height = 64;
}

//destructeur
PulsarTankers::~PulsarTankers(){}


void PulsarTankers::set_tunnel(const Tunel& h) { this->hall = h; }


void PulsarTankers::set_center(const Point& center) { this->center = center; }

long double PulsarTankers::get_speed(){
    return this->speed;
}

void PulsarTankers::set(Tunel&& h){

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

void PulsarTankers::clean(){
    this->lines.clear();
}


bool PulsarTankers::get_closer(long double h) {

    this->center = Line(this->center, this->hall.get_big_line().inLine(0.5)).inLine(h*h*std::cbrtl(h));
    this->width = 0.8 * h * this->hall.get_big_line().length();
    this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));

    this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
    this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);

    //return false;
    return intersect(this->hall.get_big_line());
}

bool PulsarTankers::intersect(Line l) {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);
}

void PulsarTankers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/pulsarTanker_PURPLE") + static_cast<std::string>(".bmp"); 

    auto image = sdl_shared(SDL_LoadBMP(path.c_str()));

    if(!image)
    {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    // dessiner le spiker
    SDL_Rect dest_rect = {static_cast<int>(x), static_cast<int>(y), init_width, init_height};
    auto monImage = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));  //La texture monImage contient maintenant l'image importée

    if (SDL_QueryTexture(monImage.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    dest_rect.w = width;
    dest_rect.h = height;

    if (SDL_RenderCopyEx(renderer.get(), monImage.get(), NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }
}