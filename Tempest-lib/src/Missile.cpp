#include "Missile.hpp"
 
    Missile::Missile(){};
    Missile::~Missile(){};

    //constructeur
    Missile::Missile(const Tunel& h){
        this->hall = h;
        this->width = h.get_big_line().length()/2.0;
        this->height = static_cast<double>(this->init_height) * static_cast<double>(this->width) / static_cast<double>(this->init_width);
        this->pos = this->hall.get_big_line().inLine(0.5);
        this->dest = this->hall.get_small_line().inLine(0.5);
        this->start = this->pos;
        this->angle = this->hall.get_angle();
    }

    Missile::Missile(const Tunel&& h){
        this->hall = h;
        this->width = h.get_big_line().length()/2.0;
        this->height = static_cast<double>(this->init_height) * static_cast<double>(this->width) / static_cast<double>(this->init_width);
        this->pos = this->hall.get_big_line().inLine(0.5);
        this->dest = this->hall.get_small_line().inLine(0.5);
        this->start = this->pos;
        this->angle = this->hall.get_angle();
    }

    int Missile::get_width() const{
        return this->width;
    }

    int Missile::get_height() const{
        return this->height;
    }

    int Missile::get_x() const{
        return this->pos.get_x();
    }

    int Missile::get_y() const{
        return this->pos.get_y();
    }

    Point Missile::get_pos() const{
        return this->pos;
    }

    void Missile::set_pos(Point pos) {
        this->pos = pos;
    }

    bool Missile::get_closer() {

        long  double h0 = this->hall.get_small_line().length() / this->hall.get_big_line().length();
        long  double z = this->pos.euclideanDistance(this->dest);
        long  double d = this->start.euclideanDistance(this->dest);
        long  double h = 1 - ( (1-h0) / (sqrt(d) ) * (sqrt(z)));

        if( !this->enemy ){
            
            this->pos = Line(this->pos, this->dest).inLine(h);
            this->width = (this->hall.get_big_line().length()/3.) * (1-h)/2.;
            this->height = this->width;
        }
        else{

            this->width = (this->hall.get_big_line().length()/3.) * (h)/2.;
            this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
            this->pos = Line(this->pos, this->dest).inLine(h);
        }

        if (this->enemy) 
            return intersect(this->hall.get_big_line());

        return intersect(this->hall.get_small_line());
    }

    bool Missile::intersect(Line l)  const{

        SDL_Rect r = {static_cast<int>(this->pos.get_x() - this->width/2), static_cast<int>(this->pos.get_y() - this->height/2), this->width, this->height};

        int x1 = l.get_p0().get_x();
        int y1 = l.get_p0().get_y();
        int x2 = l.get_p1().get_x();
        int y2 = l.get_p1().get_y();

        return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

    }

    Tunel Missile::get_hall() const {
        return this->hall;
    }

    void Missile::draw(std::shared_ptr<SDL_Renderer> renderer) {
        std::string path;
        int w,h;
        if(this->get_enemy()){
            path = "images/missile_ennemi.bmp";
            w = 537;
            h = 563;
            this->height = static_cast<double>(h) * static_cast<double>(this->width) / static_cast<double>(w);
        }
        else{
            w = init_width;
            h = init_height;
            path = "images/missile_player.bmp";

        }

        if(render_image(renderer, path.c_str(), w, h, width, height, static_cast<const int>(this->pos.get_x() - this->width/2),
                          static_cast<const int>(this->pos.get_y() - this->height/2), this->angle, NULL)){
            std::cout << "Can't load missile image" << std::endl;
            return;
        }
    }

    void Missile::set_enemy() {
        this->start = hall.get_small_line().inLine(0.5);
        this->dest = hall.get_big_line().inLine(0.5);
        this->pos = this->start;
        this->enemy = true;
    }

bool Missile::get_enemy()  const{
    return this->enemy;
}

const bool Missile::collides_with(Missile m) const {

    // Les collisions standards ne fonctionnent pas à tous les coups à cause de la durée des Timeframes.
    // On compare la distance du missile à sa destination, et la distance du missile ennemi et cette même destination.
    // Si la distance du missile ennemi est plus grande, cela veut dire que le missile l'a dépassé donc collision.
    double dist1 = this->get_pos().euclideanDistance(this->hall.get_small_line().inLine(0.5));
    double dist2 = m.get_pos().euclideanDistance(this->hall.get_small_line().inLine(0.5));

    return dist1 <= dist2;
}
