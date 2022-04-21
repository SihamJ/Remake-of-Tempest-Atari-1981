#ifndef __FLIPPERS_HPP__
#define __FLIPPERS_HPP__

#include "Enemy.hpp"

class Flippers : public Enemy {

public:

    Flippers();
    Flippers(std::string&&  name);
    Flippers(std::string&&  name, Color&& c);
    Flippers(std::string&& name,  Point&& center,  Tunel&& h);
    Flippers(const Flippers &other);
    Flippers(Flippers &&other);

    ~Flippers();

    void build() override;
    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set(Tunel&& h);
    
    std::string get_name(){ return "Flippers";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer();
    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    bool intersect(Line l);    

private:
    const int scoring=150;
    const int init_width = 128;
    const int init_height = 49;
    int width;
    int height;
};


#endif
