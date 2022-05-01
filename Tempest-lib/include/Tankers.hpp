#ifndef __TANKERS_HPP__
#define __TANKERS_HPP__

#include "Enemy.hpp"


class Tankers : public Enemy {

public:

    Tankers();
    Tankers(const std::string&&  name);
    Tankers(const std::string&&  name,const  Color&& c);
    Tankers(const std::string&& name, const  Point&& center,  const Tunel&& h);
    Tankers(const Tankers &other);
    Tankers(const Tankers &&other);

    ~Tankers();

    void clean();

    std::vector<Line> get_lines(){ return this->lines; }

    void set_dest (const Point& destination);
    void set_tunnel(const Tunel& h);
    void set_rect(const std::array<Point, 4> rect);
    void set_center(const Point& center);
    void set(Tunel&& h);
    
    const std::string get_name() const { return "Tankers";}
    const int get_scoring() const { return this->scoring;}
    bool get_closer(long double h) override;
    void draw(std::shared_ptr<SDL_Renderer> renderer) override;
    bool intersect(const Line&& l);    

private:
    const int scoring=100;
    const int init_width = 128;
    const int init_height = 49;
    int width;
    int height;
};


#endif
