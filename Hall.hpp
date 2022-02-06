#ifndef __HALL_HPP__
#define __HALL_HPP__

#include <vector>
#include <SDL.h>
#include <array>


class Hall {
    
public:
    // constructeur
    Hall(){}
    // destructeur
    ~Hall(){}

    /**
     * @brief Set the big line object
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     */
    void set_big_line (int x1, int y1, int x2, int y2) {
        bigLine = {x1, y1, x2, y2};
    }

    /**
     * @brief Set the small line object
     * 
     * @param x1 
     * @param y1 
     * @param x2 
     * @param y2 
     */
    void set_small_line (int x1, int y1, int x2, int y2) {
        smallLine = {x1, y1, x2, y2};
    }

    /**
     * @brief Get the big line object
     * 
     * @return std::array<int, 4> 
     */
    std::array<int, 4> get_big_line () {
        return bigLine;
    }

    /**
     * @brief Get the small line object
     * 
     * @return std::array<int, 4> 
     */
    std::array<int, 4> get_small_line () {
        return smallLine;
    }

    /**
     * @brief dessine les deux lignes
     * 
     * @param renderer 
     */
    void draw(SDL_Renderer* renderer) {
        SDL_RenderDrawLine(renderer, bigLine[0],bigLine[1],bigLine[2],bigLine[3]);
        SDL_RenderDrawLine(renderer, smallLine[0],smallLine[1],smallLine[2],smallLine[3]);
    }

private:
    // la petite ligne intérieur qui forme un couloir
    std::array<int, 4> bigLine;
    // la gross ligne extérieur qui forme un couloir
    std::array<int, 4> smallLine;
    
};

#endif