#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <SDL.h>
#include <array>
#include <tgmath.h>
#include <vector>
#include <string>
#include <memory>
#include "SDLWrapper.hpp"

class Point {

public:
    // Constructeur
    Point();

    Point(double x, double y);

    Point(float phi, float r);

    Point(int x, int y, float phi, float r);

    Point(const Point &other);

    Point(std::array<double, 2> point);

    // Destructeur
    ~Point();

    /**
     * @brief Set the point object
     * 
     * @param x 
     * @param y 
     */
    void set_point (double x, double y);

    /**
     * @brief Get the point object
     * 
     * @return std::array<int, 2> 
     */
    std::array<double, 2> get_point ();

    double get_x();

    double get_y();

    void set_polar(float phi, float r);

    void set_cartesian(int x, int y);
    
    std::array<float, 2> cartesian_to_polar(int x, int y);

    std::array<int, 2> polar_to_cartesian(float phi, float r);

    /**
     * @brief Dessine le point
     * 
     * @param renderer 
     */
    void draw(std::shared_ptr<SDL_Renderer> renderer);

    /**
     * @brief Set the dest object
     * 
     * @param dest 
     */
    void set_dest (std::array<double, 2> destination);
    /**
     * @brief Get the dest object
     * 
     * @return std::array<int, 2> 
     */
    std::array<double, 2> get_dest () ;

    /**
     * @brief Rapproche le point de la destination 
     * (+ ou - en fct de la variable "vitesse")
     *  
     * @return vrai si on a atteint l'objectif (= doit être détruit)
     */
    bool get_closer();

    // retourne la distance euclidienne à un autre point
    double euclideanDistance(Point p);


private:
    // + la vitesse est haute + on se rapproche du centre avec get_closer
    static int const speed = 10;
    // les coordonnées du point
    std::array<double, 2> p;
    // destination du point
    std::array<double, 2> dest;

    // coordonnées cartésiennes
    double x;
    double y;

    //coordonnées polaires
    float phi;
    float r;

};

#endif