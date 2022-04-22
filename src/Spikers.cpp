#include "../headers/Spikers.hpp"
#include <cmath>

Spikers::Spikers(){}

//constructeur
Spikers::Spikers(std::string&& name)
{
    this->name = std::move(name);
    this->width = 57;
    this->height = 64;
}

Spikers::Spikers(std::string&&  name, Color&& c)
    : Spikers(std::move(name)) 
{
    this->color = c;
}

//constructeur
Spikers::Spikers(std::string&& name,  Point&& center,  Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
    this->width = 57;
    this->height = 64;
}

// copy constructor
Spikers::Spikers(const Spikers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Spikers");
    this->width = 57;
    this->height = 64;
}

// move constructor
Spikers::Spikers(Spikers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Spikers");
    this->width = 57;
    this->height = 64;
}

//destructeur
Spikers::~Spikers(){}


// ################################################################################################ 
// ################################################################################################ 
// #################################### FIN CONSTRUCTEURS #########################################
// ################################################################################################ 
// ################################################################################################ 


void Spikers::set_tunnel(const Tunel& h){
    this->hall = h;
}

void Spikers::set_center(const Point& center){
    this->center = center;
}

const int Spikers::get_scoring() const {
    return this->scoring;
}

// ################################################################################################ 
// ################################################################################################ 

void Spikers::set(Tunel&& h){

        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_real_distribution<long double> rand (0.25, 0.75);

        this->random_p = rand(gen);
        this->random_p_init = this->random_p;
        this->hall = h;
        this->state = 0;

        // On calcule la ligne limit de déplacement du spiker (parallèle à big line)
        Point sp0 = this->hall.get_small_line().get_p0();
        Point sp1 = this->hall.get_small_line().get_p1();
        Point bp0 = this->hall.get_big_line().get_p0();
        Point bp1 = this->hall.get_big_line().get_p1();

        long double segment1 = this->random_p_init * (sp0.euclideanDistance(bp0));
        long double segment2 = this->random_p_init * (sp1.euclideanDistance(bp1));
        Line l1 = Line(sp0, bp0);
        Line l2 = Line(sp1, bp1);

        Point pp0 = l1.inLine(segment1 / l1.length());
        Point pp1 = l2.inLine(segment2 / l2.length());

        this->limit_init.set_points({pp0, pp1});


        // on calcule l'angle de rotation de l'image
        int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        width = dist/3;
        height = dist/3;

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        x = centre_small_line.get_x() - ( static_cast<long double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<long double>(height)/2.0);

        this->angle = this->hall.get_angle();
        
    }

// ################################################################################################ 
// ################################################################################################ 


bool Spikers::get_closer() {  

    Point c = hall.get_small_line().inLine(0.5);
    // std::cout << "state " << state << std::endl;
    // std::cout << "enemy center: " << center.get_x() << ", " << center.get_y() << std::endl;
    // std::cout << "small line center: " << c.get_x() << ", " << c.get_y() << std::endl;
    // std::cout << "init limit center: " << limit_init.inLine(0.5).get_x() << ", " << limit_init.inLine(0.5).get_y() << std::endl;
    // std::cout << "curr limit center: " << current_limit.inLine(0.5).get_x() << ", " << current_limit.inLine(0.5).get_y() << std::endl;

    // Update state if necessary
    // I did an overload of the oprator == in class Point to do this operation:

    if(this->state == 0 && this->center == this->limit_init.inLine(0.5))
    {
        this->state = 1;
        // this->width = (this->limit_init.length()/3.);
        // this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        // this->center = this->limit_init.inLine(0.5);
        
        // std::cout << "from state 0 to 1" << std::endl;
    }

    else if(this->state == 1 && this->center == this->hall.get_small_line().inLine(0.5))
    {
        this->state = 2;
        // this->center = this->hall.get_small_line().inLine(0.5);
        // this->width = (this->hall.get_small_line().length()/3.);
        // this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        // std::random_device rd;  // Will be used to obtain a seed for the random number engine
        // std::mt19937 gen(rd());
        // std::uniform_real_distribution<long double> rand (0.1, this->random_p_init);

        // this->random_p = rand(gen);

        // On calcule la ligne limit de déplacement courant du spiker (parallèle à big line)
        // Formule de THALES
        // Point sp0 = this->hall.get_small_line().get_p0();
        // Point sp1 = this->hall.get_small_line().get_p1();
        // Point bp0 = this->hall.get_big_line().get_p0();
        // Point bp1 = this->hall.get_big_line().get_p1();

        // long double segment1 = this->random_p * (sp0.euclideanDistance(bp0));
        // long double segment2 = this->random_p * (sp1.euclideanDistance(bp1));
        // Line l1 = Line(sp0, bp0);
        // Line l2 = Line(sp1, bp1);

        // Point pp0 = l1.inLine(segment1 / l1.length());
        // Point pp1 = l2.inLine(segment2 / l2.length());

        // this->current_limit.set_points({pp0, pp1});
        // std::cout << "from state 1 to 2" << std::endl;
        this->current_limit = this->limit_init;
    }

    else if(this->state == 2 && this->center == this->current_limit.inLine(0.5))
    {
        this->state = -1;
        // this->center = this->hall.get_small_line().inLine(0.5);
        // this->width = (this->hall.get_small_line().length()/3.);
        // this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        // std::cout << "from state 2 to 3" << std::endl;
    }

    // cet état sera supprimé
    else if(this->state == 3 && this->center == this->hall.get_small_line().inLine(0.5))
    {
        this->state = -1;
        // this->center = this->current_limit.inLine(0.5);
        // this->width = (this->current_limit.length()/3.);
        // this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_real_distribution<long double> rand (0.1, this->random_p_init);

        this->random_p = rand(gen);

        // On calcule la ligne limit de déplacement courant du spiker (parallèle à big line)
        // Formule de THALES
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

        this->current_limit.set_points({pp0, pp1});

        // std::cout << "from state 3 to 2" << std::endl;
    }

    
    // Movement
    if (this->state == 0){

        long double h0 =  this->speed;//(this->hall.get_small_line().length() / this->limit_init.length());
        long double z = this->center.euclideanDistance(this->limit_init.inLine(0.5));
        long double d = this->hall.get_small_line().inLine(0.5).euclideanDistance(this->limit_init.inLine(0.5));
        long double h = (1. - ((1.-h0) / (d*d)) * (z*z));

        this->center = Line(this->hall.get_small_line().inLine(0.5), this->limit_init.inLine(0.5)).inLine(h);

        this->width = h * (this->limit_init.length()/3.);
        this->height = this->width;//<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
    }

    else if(this->state == 1){

        long double h0 = this->speed;//(this->hall.get_small_line().length() / this->limit_init.length());
        long double z = this->center.euclideanDistance(this->hall.get_small_line().inLine(0.5));
        long double d = this->hall.get_small_line().inLine(0.5).euclideanDistance(this->limit_init.inLine(0.5));
        long double h = (1. - ((1.-h0) / (d*d)) * (z*z));

        this->center = Line(this->limit_init.inLine(0.5), this->hall.get_small_line().inLine(0.5)).inLine(h);

        this->width = (this->limit_init.length()/3.) * (1-h) ;
        this->height = this->width;//<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
    }

    // TO DO changer déplacement ennemi en envoie d'un missile ennemi
    else if(this->state == 2){

        long double h0 = this->speed;//(this->hall.get_small_line().length() / this->current_limit.length());
        long double z = this->center.euclideanDistance(this->current_limit.inLine(0.5));
        long double d = this->hall.get_small_line().inLine(0.5).euclideanDistance(this->current_limit.inLine(0.5));
        long double h = (1. - ((1.-h0) / (d*d)) * (z*z));

        this->center = Line(this->hall.get_small_line().inLine(0.5), this->current_limit.inLine(0.5)).inLine(h);

        this->width = h * (this->current_limit.length()/3.);
        this->height = this->width;// * static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);

    }
    // Cet état sera supprimé
    else if(this->state == 3){

        long double h0 = this->speed;//(this->hall.get_small_line().length() / this->current_limit.length());
        long double z = this->center.euclideanDistance(this->hall.get_small_line().inLine(0.5));
        long double d = this->hall.get_small_line().inLine(0.5).euclideanDistance(this->current_limit.inLine(0.5));
        long double h = (1. - ((1.-h0) / (d*d)) * (z*z));

        this->center = Line(this->current_limit.inLine(0.5), this->hall.get_small_line().inLine(0.5)).inLine(h);

        this->width = (this->hall.get_small_line().length()/3.) *(1-h);
        this->height = this->width;//static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));

        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);

    }
    return false;
    //return intersect(this->hall.get_big_line());
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

    if (this->state != - 1){
        std::string path;
        path = static_cast<std::string>("images/spiker_") + this->color.get_name() + static_cast<std::string>(".bmp"); 

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

    Point center_small_line = hall.get_small_line().inLine(0.5);
    // this->limit_init.draw(renderer);
    // this->current_limit.draw(renderer);

    if (state == 0) {
        Line l(center_small_line, this->center);
        l.draw(renderer);
    }

    else {
        Line l(center_small_line, this->limit_init.inLine(0.5));
        l.draw(renderer);
    }
}

Line Spikers::get_line_current_limit() {
    return this->current_limit;
}
    
void Spikers::decrease_random_p() {
    this->random_p -= 0.5;
    if (random_p < 0.) random_p = 0.;
}

void Spikers::update_line_limit() {
    // On calcule la ligne limit de déplacement du spiker (parallèle à big line)
    Point sp0 = this->hall.get_small_line().get_p0();
    Point sp1 = this->hall.get_small_line().get_p1();
    Point bp0 = this->hall.get_big_line().get_p0();
    Point bp1 = this->hall.get_big_line().get_p1();

    long double segment1 = this->random_p_init * (sp0.euclideanDistance(bp0));
    long double segment2 = this->random_p_init * (sp1.euclideanDistance(bp1));
    Line l1 = Line(sp0, bp0);
    Line l2 = Line(sp1, bp1);

    Point pp0 = l1.inLine(segment1 / l1.length());
    Point pp1 = l2.inLine(segment2 / l2.length());

    this->limit_init.set_points({pp0, pp1});

}