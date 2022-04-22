#include "../headers/Flippers.hpp"

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


void Flippers::set(Tunel&& h){

        this->hall = h;

        double dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist/2.;
        this->height = static_cast<double>(init_height) * ( static_cast<double>(width) / static_cast<double>(init_width));

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - ( static_cast<double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<double>(height)/2.0);

        this->angle = this->hall.get_angle();

    }

void Flippers::clean(){
    this->lines.clear();
}


bool Flippers::get_closer() {

    double h0 = this->speed * this->hall.get_small_line().length() / this->hall.get_big_line().length();
    double z = this->center.euclideanDistance(this->hall.get_big_line().inLine(0.5));
    double d = this->hall.get_small_line().inLine(0.5).euclideanDistance(this->hall.get_big_line().inLine(0.5));
    double h = 1 - ((1-h0) / (d*d)) * (z*z);

    this->center = Line(this->hall.get_small_line().inLine(0.5), this->hall.get_big_line().inLine(0.5)).inLine(h);
    this->width = h * this->hall.get_big_line().length();
    this->height = static_cast<double>(init_height) * ( static_cast<double>(width) / static_cast<double>(init_width));

    this->x = this->center.get_x() - ( static_cast<double>(this->width)/2.0);
    this->y = this->center.get_y() - ( static_cast<double>(this->height)/2.0);

    //return false;
    return intersect(this->hall.get_big_line());
}

bool Flippers::intersect(Line l) {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

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
}