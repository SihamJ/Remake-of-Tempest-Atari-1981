#include "../headers/Tankers.hpp"

Tankers::Tankers(){}

//constructeur
Tankers::Tankers(std::string&& name)
{
    this->name = std::move(name);
}

Tankers::Tankers(std::string&& name, Color&& c)
    : Enemy(std::move(c))
{
    this->name = std::move(name);
}

//constructeur
Tankers::Tankers(std::string&& name,  Point&& center,  Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
}

// copy constructor
Tankers::Tankers(const Tankers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Tankers");
}

Tankers::Tankers(Tankers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Tankers");
    this->width = 57;
    this->height = 64;
}

//destructeur
Tankers::~Tankers(){}


void Tankers::set_tunnel(const Tunel& h) { this->hall = h; }


void Tankers::set_center(const Point& center) { this->center = center; }


void Tankers::set(Tunel&& h){

        this->hall = h;

        double dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist/2.;
        this->height = static_cast<double>(init_height) * ( static_cast<double>(width) / static_cast<double>(init_width));

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - ( static_cast<double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<double>(height)/2.0);

        bool cond1 = false;

        double segment_a = centre_big_line.get_x() - centre_small_line.get_x();
        double segment_b = centre_big_line.get_y() - centre_small_line.get_y();
        double segment_c = sqrt(segment_a * segment_a + segment_b * segment_b);

        if(this->hall.get_small_line().get_p0().get_y() == this->hall.get_small_line().get_p1().get_y()){
            this->angle = 0.;
            return;
        }
        if(this->hall.get_small_line().get_p0().get_x() == this->hall.get_small_line().get_p1().get_x()){
            this->angle = 90.;
            return;
        }

        if(segment_a < 0. && segment_b < 0.0) {
            this->angle = -acos( segment_a / segment_c ) * (180.0/3.141592653589793238463) - 90.;
        }
        else if (segment_a < 0. && segment_b > 0.0) {
            this->angle = acos( - segment_b / segment_c ) * (180.0/3.141592653589793238463);
        }
        else if(segment_a > 0. && segment_b < 0.) {
            this->angle = acos( - segment_a / segment_c ) * (180.0/3.141592653589793238463) + 90.;
        }
        else if(segment_a > 0. && segment_b > 0.) {
            this->angle = -acos( segment_b / segment_c )  * (180.0/3.141592653589793238463);
        }
        else {
            this->angle = 0.;
        }

    }

void Tankers::clean(){
    this->lines.clear();
}


bool Tankers::get_closer() {

    double h0 = this->hall.get_small_line().length() / this->hall.get_big_line().length();
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

bool Tankers::intersect(Line l) {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);
}

void Tankers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/tanker_") + this->color.get_name() + static_cast<std::string>(".bmp"); 

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