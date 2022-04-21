#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();
    Flippers(std::string  name);
    Flippers(std::string  name, Color& c);
    Flippers(std::string name, const Point& center, const Tunel& h, const std::array<Point, 4> &rect);
    Flippers(const Flippers &other);

    ~Flippers();

    std::vector<Line> get_lines(){ return this->lines; }

    void build() override;
    void clean();
    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    const int get_scoring() override;

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    
    void set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect) override;
    std::string get_name() override { return "Flippers";}
    bool get_closer() override;
    bool intersect(Line l);    


private:

    std::vector<Line> lines;
    Color color;

    // nb de points gagnés par le joueur s'il tue un flipper
    const int scoring=150;
    
    // taille initial de l'image
    const int init_width = 128;
    const int init_height = 49;
    
};


#endif