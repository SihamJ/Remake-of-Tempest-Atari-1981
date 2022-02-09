#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <SDL.h>
#include <array>

// classe de test inutile, sûrement à supprimer
class Map {
    
public:
    Map(){}
    ~Map(){}
    void add_lines (int x1, int y1, int x2, int y2) {
        std::array<int, 4> a{{x1, y1, x2, y2}};
        lines.push_back(a);
    }

    void draw(SDL_Renderer* renderer) {
        for (auto i : lines) {
            SDL_RenderDrawLine(renderer, i[0],i[1],i[2],i[3]);
        }
    }

private:
    std::vector<std::array<int, 4>> lines;

};

#endif