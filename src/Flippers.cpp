#include "../headers/Flippers.hpp"

Flippers::Flippers(){}

//constructeur
Flippers::Flippers(std::string&& name)
{
    this->name = std::move(name);
    this->width = init_width;
    this->height = init_height;
}

Flippers::Flippers(std::string&&  name, Color&& c)
    : Enemy(std::move(c))
{
    this->name = name;
    this->width = init_width;
    this->height = init_height;
}

//constructeur
Flippers::Flippers(std::string&& name, Point&& center, Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
    this->width = init_width;
    this->height = init_height;
    build();
}

// copy constructor
Flippers::Flippers(const Flippers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Flippers");
    this->width = init_width;
    this->height = init_height;
    build();
}

// move constructor
Flippers::Flippers(Flippers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Flippers");
    this->width = init_width;
    this->height = init_height;
    build();
}

//destructeur
Flippers::~Flippers(){}



void Flippers::set_dest (Point&& destination){
    this->dest = std::move(destination);
}

void Flippers::set_tunnel(Tunel&& h){
    this->hall = std::move(h);
}

void Flippers::set_rect(std::array<Point, 4>&& rect){
    this->rect = std::move(rect);
}

void Flippers::set_center(Point&& center){
    this->center = std::move(center);
}

const int Flippers::get_scoring() const {
    return this->scoring;
}

void Flippers::build() {}

void Flippers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/flipper_") + this->color.get_name() + static_cast<std::string>(".bmp"); 

    SDL_Surface* image = SDL_LoadBMP(path.c_str());

    if(!image)
    {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    // dessiner le flipper
    SDL_Rect dest_rect = {static_cast<int>(x), static_cast<int>(y), init_width, init_height};
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer.get(), image);  //La texture monImage contient maintenant l'image importée
    SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface

    if (SDL_QueryTexture(monImage, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

    dest_rect.w = width;
    dest_rect.h = height;

   // std::cout << "angle: " << angle << std::endl; 
    if (SDL_RenderCopyEx(renderer.get(), monImage, NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return;
    }

}


bool Flippers::get_closer() {

    Point pos{this->x, this->y};
    Line trajectoire{this->start, this->dest};

    double h0 = 0.03;
    double z = pos.euclideanDistance(this->dest);
    double d = this->start.euclideanDistance(this->dest);

    double ratio = 1 - ( (1-h0) / (d*d) ) * (z*z);

    pos = trajectoire.inLine(ratio);

    this->x = pos.get_x();
    this->y = pos.get_x();

    // double a = Line(this->start, Point(x,y)).length();
    // double b = Line(this->start, Point(this->pos.))

    // double diff = sqrt(a*a -  )
    //this->width = static_cast<int>(static_cast<float>(this->width) * (1.0 + ratio));
   // this->height = static_cast<int>(static_cast<float>(init_height) * ( static_cast<float>(width) / static_cast<float>(init_width))); 
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

void Flippers::clean(){
    this->lines.clear();
}

void Flippers::set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect){

        this->center = center;
        this->hall = h;
        this->rect = rect;
        Line s = this->hall.get_small_line();
        Line b = this->hall.get_big_line();

        this->start = s.get_p0();
        this->dest = b.get_p0();

        int dist = s.get_p0().euclideanDistance(s.get_p1());
        width = dist;
        height =  static_cast<int>(static_cast<float>(init_height) * ( static_cast<float>(width) / static_cast<float>(init_width)));

        x = s.get_p0().get_x();
        y = s.get_p0().get_y();


        // Le flipper devra s'adapter selon le couloir
        if(s.get_p0().get_y() >=  b.get_p0().get_y() && s.get_p0().get_x() >= b.get_p0().get_x()){
            this->angle = 180;
            this->angle += (acos( Line(s.get_p0(), Point(s.get_p0().get_x(),s.get_p1().get_y())).length() / s.length())) * (180.0 / 3.14159265358979323846);
        }
        else if(s.get_p0().get_y() >=  b.get_p0().get_y() && s.get_p0().get_x() <= b.get_p0().get_x()){
            this->angle = 180;
            this->angle -= (acos( Line(s.get_p0(), Point(s.get_p0().get_x(),s.get_p1().get_y())).length() / s.length())) * (180.0 / 3.14159265358979323846);
        }
        else if(s.get_p0().get_y() <=  b.get_p0().get_y() && s.get_p0().get_x() >= b.get_p0().get_x()){
            this->angle = -(acos( Line(s.get_p0(), Point(s.get_p0().get_x(),s.get_p1().get_y())).length() / s.length())) * (180.0 / 3.14159265358979323846);
        }
        else 
            this->angle = (acos( Line(s.get_p0(), Point(s.get_p1().get_x(),s.get_p0().get_y())).length() / s.length())) * (180.0 / 3.14159265358979323846);
        
    }