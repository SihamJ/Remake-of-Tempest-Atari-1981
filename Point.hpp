#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <SDL.h>
#include <array>


class Point {

public:
    // Constructeur
    Point(){}
    // Destructeur
    ~Point(){}

    /**
     * @brief Set the point object
     * 
     * @param x 
     * @param y 
     */
    void set_point (int x, int y) {
        p = {x, y};
    }

    /**
     * @brief Get the point object
     * 
     * @return std::array<int, 2> 
     */
    std::array<int, 2> get_point () {
        return p;
    }

    /**
     * @brief Dessine le point
     * 
     * @param renderer 
     */
    void draw(SDL_Renderer* renderer) {
        SDL_RenderDrawPoint(renderer, p[0], p[1]);
    }

    /**
     * @brief Rapproche le point du centre 
     * (+ ou - en fct de la variable "vitesse")
     * 
     * @param centre 
     */
    void get_closer(class Point centre) {
        std::array<int, 2> p_centre = centre.get_point();
        int diff_x = p_centre[0] - p[0];
        int diff_y = p_centre[1] - p[1];
        int coeff_x = (diff_x > 0) ? 1 : -1;
        int coeff_y = (diff_y > 0) ? 1 : -1;
        if (diff_x != 0 || diff_y != 0) {
            p[0] += vitesse * diff_x / (coeff_x * diff_x + coeff_y * diff_y);
            p[1] += vitesse * diff_y / (coeff_x * diff_x + coeff_y * diff_y);
        }
        int nv_coeff_x = ((p_centre[0] - p[0]) > 0) ? 1 : -1;
        int nv_coeff_y = ((p_centre[1] - p[1]) > 0) ? 1 : -1;

        // Si ça dépasse le centre, les points sont "détruits"
        if ((nv_coeff_x != coeff_x) || (nv_coeff_y != coeff_y)) {
            p[0] = p_centre[0];
            p[1] = p_centre[1];
        }
    }

private:
    // + la vitesse est haute + on se rapproche du centre avec get_closer
    static int const vitesse = 50;
    // les coordonnées du point
    std::array<int, 2> p;

};

#endif