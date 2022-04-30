#include "Spikers.hpp"


#define RATIO_RANDOM_P 0.75

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

void Spikers::set_state(int state) {
    this->state = state;
}

const int Spikers::get_scoring() const {
    return this->scoring;
}

const int Spikers::get_state() const {
    return this->state;
}

Line Spikers::get_limit()const {
    return this->limit_init;
}

// ################################################################################################ 
// ################################################################################################ 

void Spikers::set(Tunel&& h){

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
        this->start = this->hall.get_small_line();

        int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist/3;
        this->height = dist/3;

        Point centre_small_line = hall.get_small_line().inLine(0.5);
        this->center = centre_small_line;

        Point centre_big_line = hall.get_big_line().inLine(0.5);

        this->x = centre_small_line.get_x() - ( static_cast<long double>(width)/2.0);
        this->y = centre_small_line.get_y() - ( static_cast<long double>(height)/2.0);

        this->angle = this->hall.get_angle();
        
    }

// ################################################################################################ 
// ################################################################################################ 


bool Spikers::get_closer(long double h) {  

    Point c = hall.get_small_line().inLine(0.5);

    if(this->state == 0 && this->center == this->limit_init.inLine(0.5))
    {
        this->state = 1;
    }
    else if(this->state == 1 && this->center == this->hall.get_small_line().inLine(0.5))
    {
        this->state = 2;
    }
    else if(this->state == 2 && this->center == this->limit_init.inLine(0.5))
    {
        this->state = -1;
    }
    
    
    // Movement
    if (this->state == 0){

        if (random_p < RATIO_RANDOM_P) {
            double dist1 = static_cast<double>(hall.get_small_line().inLine(0.5).euclideanDistance(this->center));
            double dist2 = static_cast<double>(hall.get_small_line().inLine(0.5).euclideanDistance(hall.get_big_line().inLine(0.5)));

            random_p = dist1/dist2;
            
            update_line_limit();
            state = -1;
            return false;
        }

        this->center = Line(this->center, this->limit_init.inLine(0.5)).inLine(h*h*std::cbrtl(h));
        this->width = h * this->limit_init.length()/3.;
        this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
        this->angle = 2*360*h;
    }

    else if(this->state == 1) {
        this->center = Line(this->center, this->hall.get_small_line().inLine(0.5)).inLine(h*std::cbrtl(h));
        this->width = (this->limit_init.length()/3.) * (1-h) ;
        this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
        this->angle = -2*360*h;
    }

    // Update state if necessary
    // I did an overload of the oprator == in class Point to do this operation:
    if(this->state == 0 && this->center == this->limit_init.inLine(0.5))
    {
        this->state = 1;
    }

    else if(this->state == 1 && this->center == this->hall.get_small_line().inLine(0.5))
    {
        this->state = 2;
    }

    else if (state == -1 && random_p == 0.) return true;

    
    return false;
    //return intersect(this->hall.get_big_line());
}

bool Spikers::intersect(Line l) const {
    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), this->width, this->height};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

}

void Spikers::draw(std::shared_ptr<SDL_Renderer> renderer) {

    if (this->state != - 1){
        std::string path;
        path = static_cast<std::string>("images/spiker_") + this->color.get_name() + static_cast<std::string>(".bmp"); 

        if(render_image(renderer, path, this->init_width, this->init_height, this->width, this->height, static_cast<const int>(x),  static_cast<const int>(y), 
                    this->angle, NULL)){
            std::cout << "Can't load spikers image" <<std::endl;
            return;
        }
    }

    Point center_small_line = hall.get_small_line().inLine(0.5);

    if (state == 0 && center_small_line.euclideanDistance(this->center) > 0) {
        Line l(center_small_line, this->center);
        l.draw(renderer);
    }
    else if(state != 0) {
        Line l(center_small_line, this->limit_init.inLine(0.5));
        l.draw(renderer);
    }
}

Line Spikers::get_line_limit() const {
    return this->limit_init;
}
    
bool Spikers::decrease_random_p() {
    if (this->state == 0) {
        double dist1 = static_cast<double>(hall.get_small_line().inLine(0.5).euclideanDistance(this->center));
        double dist2 = static_cast<double>(hall.get_small_line().inLine(0.5).euclideanDistance(hall.get_big_line().inLine(0.5)));

        random_p = dist1/dist2;
        
        update_line_limit();

        state = -1;

        return true;
    }
    
    this->random_p -= 0.05;
    if (random_p <= 0.) return true;

    return false;
}

void Spikers::update_line_limit() {
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

}

