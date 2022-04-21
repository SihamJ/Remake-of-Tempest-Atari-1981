#include "../headers/Color.hpp"


Color::Color(){}

Color::Color(std::string&& name, std::string&& stream)
    : name(std::move(name))
{
    std::string c = stream;
    std::string r = c.substr(0, 3);
    std::string g = c.substr(3, 3);
    std::string b = c.substr(6, 3);

    this->r = std::stoi(r);
    this->g = std::stoi(g);
    this->b = std::stoi(b);
    this->a = 255;
}

Color::Color(std::string&& name, const int& r, const int& g, const int& b)
    : name(std::move(name)), r(r), g(g), b(b)
{

}

// constructor for manually defining rgb values
Color::Color(std::string&& name, const int& r, const int& g, const int& b, const int& a)
    : name(std::move(name)), r(r), g(g), b(b), a(a)
{
    
}

// constructor to be used with the predefined colors in utils.h
// stream is a string describing the rgb values
Color::Color(std::string&& name, std::string&& stream, const int& a)
    : name(std::move(name)), a(a)
{
    std::string c = stream;
    std::string r = c.substr(0, 3);
    std::string g = c.substr(3, 3);
    std::string b = c.substr(6, 3);

    this->r = std::stoi(r);
    this->g = std::stoi(g);
    this->b = std::stoi(b);
}


Color::~Color(){}

// get red value
const int Color::get_r(){
    return this->r;
}

// get green value
const int Color::get_g(){
    return this->g;
}

// get blue value
const int Color::get_b(){
    return this->b;
}

// get opacity value
const int Color::get_a(){
    return this->a;
}

const std::string Color::get_name(){
    return this->name;
}

