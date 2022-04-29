#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include <string>
#include <array>
#include <SDL.h>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <memory>
#include "Utils.hpp"
#include "Color.hpp"
#include "SDLWrapper.hpp"
#include "Line.hpp"


class TextRenderer
{
    public:

        static std::vector<int> parse_score(int value);
        static void draw_caracter(std::shared_ptr<SDL_Renderer> renderer, char c, int x, int y, float size, int thickness);
        static void draw_text(std::shared_ptr<SDL_Renderer> renderer, const std::string&& text, int x, int y, float size, int thickness);
        static void draw_life(std::shared_ptr<SDL_Renderer> renderer, int value, int x, int y, const std::string&& color);
        
    private:

        TextRenderer();
        ~TextRenderer();

        static const std::array<std::array<int, 112>, 95> coord;

};




#endif