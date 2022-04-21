#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();
    Flippers(std::string&& name);
    Flippers(std::string&& name, Color&& c);
    Flippers(std::string&& name, Point&& center, Tunel&& h);
    Flippers(const Flippers &other);
    Flippers(Flippers &&other);

    ~Flippers();

    std::vector<Line> get_lines(){ return this->lines; }

    void build() override;
    void clean();
    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    const int get_scoring() const override;

    void set_dest (Point&& destination);
    void set_tunnel(Tunel&& h);
    void set_rect(std::array<Point, 4>&& rect);
    void set_center(Point&& center);
    
    void set(Point&& center, Point&& start, Tunel&& h, std::array<Point, 4> &&rect) override;
    const std::string get_name() const  override { return this->name;}
    bool get_closer() override;
    bool intersect(Line l);    


private:

    // nb de points gagnés par le joueur s'il tue un flipper
    const int scoring=150;
    
    // taille initial de l'image
    const int init_width = 128;
    const int init_height = 49;
    
};


#endif