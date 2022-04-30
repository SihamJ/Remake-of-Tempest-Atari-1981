#ifndef __FUSEBALLS_HPP__
#define __FUSEBALLS_HPP__

#include "Enemy.hpp"


class Fuseballs : public Enemy {

public:

    Fuseballs();
    Fuseballs(const std::string&&  name);
    Fuseballs(const std::string&&  name, const  Color&& c);
    Fuseballs(const std::string&& name, const  Point&& center, const  Tunel&& h);
    Fuseballs(const Fuseballs &other);
    Fuseballs(const Fuseballs &&other);

    ~Fuseballs();

    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set(Tunel&& h);
    
    std::string get_name(){ return "Fuseballs";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer(long double h) override;

    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    bool intersect(Line l);    

private:
    const int scoring=250;
    const int init_width = 128;
    const int init_height = 49;
    int width;
    int height;
};


#endif
