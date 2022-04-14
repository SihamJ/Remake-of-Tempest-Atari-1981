#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <string>
#include <iostream>
#include <iterator>
#include "utils.hpp"

class Color {
    public:
        Color();

        Color(const int& r, const int& g, const int& b);
        Color(std::string&& stream);

        Color(const int& r, const int& g, const int& b, const int& a);
        Color(std::string&& stream, const int& opacity);



        ~Color();

        const int get_r();
        const int get_g();
        const int get_b();
        const int get_a();
        const void print();

    private:
        int r;
        int g;
        int b;
        int a=255;
};


#endif