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
     * @brief Set the dest object
     * 
     * @param dest 
     */
    void set_dest (std::array<int, 2> destination) {
        dest = destination;
    }

    /**
     * @brief Get the dest object
     * 
     * @return std::array<int, 2> 
     */
    std::array<int, 2> get_dest () {
        return dest;
    }

    /**
     * @brief Rapproche le point de la destination 
     * (+ ou - en fct de la variable "vitesse")
     *  
     * @return vrai si on a atteint l'objectif (= doit être détruit)
     */
    bool get_closer() {
        int diff_x = dest[0] - p[0];
        int diff_y = dest[1] - p[1];
        int coeff_x = (diff_x > 0) ? 1 : -1;
        int coeff_y = (diff_y > 0) ? 1 : -1;
        if (diff_x != 0 || diff_y != 0) {
            p[0] += speed * diff_x / (coeff_x * diff_x + coeff_y * diff_y);
            p[1] += speed * diff_y / (coeff_x * diff_x + coeff_y * diff_y);
        }
        int nv_coeff_x = ((dest[0] - p[0]) > 0) ? 1 : -1;
        int nv_coeff_y = ((dest[1] - p[1]) > 0) ? 1 : -1;

        // Si ça dépasse le centre, les points sont "détruits"
        if ((nv_coeff_x != coeff_x) || (nv_coeff_y != coeff_y) || (p == dest)) {
            return true;
        }
        return false;
    }

private:
    // + la vitesse est haute + on se rapproche du centre avec get_closer
    static int const speed = 3;
    // les coordonnées du point
    std::array<int, 2> p;
    // destination du point
    std::array<int, 2> dest;

};

#endif