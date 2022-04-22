#ifndef __TANKERS_HPP__
#define __TANKERS_HPP__

#include "Enemy.hpp"

class Tankers : public Enemy {

public:

    Tankers();
    Tankers(std::string&&  name);
    Tankers(std::string&&  name, Color&& c);
    Tankers(std::string&& name,  Point&& center,  Tunel&& h);
    Tankers(const Tankers &other);
    Tankers(Tankers &&other);

    ~Tankers();

    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set(Tunel&& h);
    
    std::string get_name(){ return "Tankers";}
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
