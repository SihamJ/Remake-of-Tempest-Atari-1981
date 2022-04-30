#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <string>
#include <iostream>
#include <iterator>
#include "Utils.hpp"


class Color {
    public:
        Color();

        Color(std::string&& name, const int& r, const int& g, const int& b);
        Color(std::string&& name, std::string&& stream);

        Color(const std::string& name, const int& r, const int& g, const int& b);
        Color(const std::string& name, const std::string& stream);

        Color(std::string&& name, const int& r, const int& g, const int& b, const int& a);
        Color(std::string&& name, std::string&& stream, const int& opacity);

        Color(const std::string& name, const int& r, const int& g, const int& b, const int& a);
        Color(const std::string& name, const std::string& stream, const int& a);

        ~Color();

        const int get_r() const;
        const int get_g() const;
        const int get_b() const;
        const int get_a() const;
        const std::string get_name() const;

    private:
        int r;
        int g;
        int b;
        int a=255;
        std::string name;
};


#endif