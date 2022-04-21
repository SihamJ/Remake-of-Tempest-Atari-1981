#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "Point.hpp"
#include "Line.hpp"
#include "Tunel.hpp"

class Missile {
    public:
        Missile(){};
        ~Missile(){};

        //constructeur
        Missile(const Tunel& h)
        {
            this->hall = h;
        }

        int get_width(){
            return this->width;
        }

        int get_height(){
            return this->height;
        }

        int get_x(){
            return this->pos.get_x();
        }

        int get_y(){
            return this->pos.get_y();
        }

        Point get_pos(){
            return this->pos;
        }

        void set(Tunel&& h){

            std::cout << "moved values for Missile" << std::endl;
            this->hall = h;

            int dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
            this->width = dist/2.0;
            this->height = dist/2.0;

            this->pos = h.get_big_line().inLine(0.5);

            this->dest = h.get_small_line().inLine(0.5);
            this->start = this->pos;
        }


        bool get_closer(){


            double h0 = 0.03;
            double z = this->pos.euclideanDistance(this->dest);
            double d = this->start.euclideanDistance(this->dest);

            double ratio = 1 - ( (1-h0) / (d*d) ) * (z*z);
            this->pos = Line(this->start, this->dest).inLine(ratio);

            return intersect(this->hall.get_small_line());
        }

        bool intersect(Line l) {
            SDL_Rect r = {static_cast<int>(this->pos.get_x()), static_cast<int>(this->pos.get_y()), this->width, this->height};

            int x1 = l.get_p0().get_x();
            int y1 = l.get_p0().get_y();
            int x2 = l.get_p1().get_x();
            int y2 = l.get_p1().get_y();

            // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

            return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);

        }

        void draw(std::shared_ptr<SDL_Renderer> renderer) {
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

            if (SDL_RenderCopyEx(renderer.get(), monImage, NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE) != 0) {
                SDL_Log("Erreur > %s", SDL_GetError());
                return;
            }
        }

    private:


        // + la vitesse est haute + on se rapproche du centre avec get_closer
        int speed = 10;
        double ratio = 0;
        // couloir auquel appartient l'ennemi
        Tunel hall;

        Point dest;
        Point start;
        Point pos;

        Line trajectoire;

        // coordonnee de l'image (top left corner du carré)
        // double x, y;

        // taille initial de l'image
        const int init_width = 57;
        const int init_height = 64;

        // taille à changer pr agrandir ou rétrécir l'image de l'ennemi
        int width = 57;
        int height = 64;

        // angle de rotation de l'image
        double angle;
};



#endif