#include "../headers/Missile.hpp"
 
    Missile::Missile(){};
    Missile::~Missile(){};

    //constructeur
    Missile::Missile(const Tunel& h){
        this->hall = h;
        int dist = this->hall.get_small_line().get_p0().euclideanDistance(this->hall.get_small_line().get_p1());
        this->width = dist/2.0;
        this->height = dist/2.0;
        this->pos = this->hall.get_big_line().inLine(0.5);
        this->dest = this->hall.get_small_line().inLine(0.5);
        this->start = this->pos;
        this->angle = this->hall.get_angle();
    }

    Missile::Missile(const Tunel&& h){
        this->hall = std::move(h);
        int dist = this->hall.get_small_line().get_p0().euclideanDistance(this->hall.get_small_line().get_p1());
        this->width = dist/2.0;
        this->height = dist/2.0;
        this->pos = this->hall.get_big_line().inLine(0.5);
        this->dest = this->hall.get_small_line().inLine(0.5);
        this->start = this->pos;
        this->angle = this->hall.get_angle();
    }

    int Missile::get_width(){
        return this->width;
    }

    int Missile::get_height(){
        return this->height;
    }

    int Missile::get_x(){
        return this->pos.get_x();
    }

    int Missile::get_y(){
        return this->pos.get_y();
    }

    Point Missile::get_pos(){
        return this->pos;
    }

    bool Missile::get_closer(){

        long  double h0 = this->hall.get_small_line().length() / this->hall.get_big_line().length();
        long  double z = this->pos.euclideanDistance(this->dest);
        long  double d = this->start.euclideanDistance(this->dest);

        long  double h = 1 - ( (1-h0) / (sqrt(d) ) * (sqrt(z)));

        this->pos = Line(this->pos, this->dest).inLine(h);

        this->width = (this->hall.get_big_line().length()/3.) * (1-h) / 3.;
        this->height = this->width;

        return intersect(this->hall.get_small_line());
    }

    bool Missile::intersect(Line l) {

        SDL_Rect r = {static_cast<int>(this->pos.get_x()), static_cast<int>(this->pos.get_y()), this->width, this->height};

        int x1 = l.get_p0().get_x();
        int y1 = l.get_p0().get_y();
        int x2 = l.get_p1().get_x();
        int y2 = l.get_p1().get_y();

        // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

        return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

    }

    Tunel Missile::get_hall() {
        return this->hall;
    }

    void Missile::draw(std::shared_ptr<SDL_Renderer> renderer) {
        SDL_Surface* image = SDL_LoadBMP("images/missile.bmp");
        if(!image)
        {
            SDL_Log("Erreur > %s", SDL_GetError());
            return;
        }

        // dessiner le spiker
        SDL_Rect dest_rect = { static_cast<int>(this->pos.get_x()), static_cast<int>(this->pos.get_y()), init_width, init_height};
        SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer.get(), image);  //La texture monImage contient maintenant l'image importée
        SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface

        if (SDL_QueryTexture(monImage, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
            SDL_Log("Erreur > %s", SDL_GetError());
            return;
        }

        dest_rect.w = width;
        dest_rect.h = height;

        if (SDL_RenderCopyEx(renderer.get(), monImage, NULL, &dest_rect, this->angle, NULL, SDL_FLIP_NONE) != 0) {
            SDL_Log("Erreur > %s", SDL_GetError());
            return;
        }
    }
