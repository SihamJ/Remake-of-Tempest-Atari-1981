#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Tube.hpp"
#include "Enemy.hpp"
#include "TriangleMap.hpp"
#include "SquareMap.hpp"
#include "CircleMap.hpp"
#include "Flippers.hpp"
#include "Tankers.hpp"
#include "Spikers.hpp"
#include "Fuseballs.hpp"
#include "Pulsars.hpp"
#include "PulsarTankers.hpp"
#include "FuseballTankers.hpp"
#include "Utils.hpp"
#include "Color.hpp"
#include <random>

class Level {
    public:
        Level();
        Level(int a);
        ~Level();

        std::shared_ptr<Tube> get_map();
        int get_current_level();
        std::map<int, Color> get_enemies();
        Color get_player_color();
        Color get_map_color();
        Color get_score_color();
        const int get_nb_enemies();
        void next_level();
        std::shared_ptr<Enemy> new_enemy();
        void print();
        long double get_h(long double h0, long double d, long double z, bool backwards);

    private:
        void set_map();
        void set_enemies();
        void set_player_color();
        void set_current_level(int level);
        int current_level = 0;
        std::shared_ptr<Tube> map;
        std::map<int, Color> current_enemies;
        Color current_player_color;
        int current_level_time = 15;

        // description des différents niveaux, leurs ennemies, map et couleurs.
        // Il n'y a qu'une seule instance de Level dans ce jeu, qui se met à jour au fur et à mesure que le joueur progresse,
        // et récupère les variables statiques ci-dessous pour construire la scène

        const std::map<int, Color> level1_16_characters  =  { { enemies_list::superzapper, Color("YELLOW", YELLOW) }, 
                                                                    { enemies_list::flippers, Color("RED", RED) }, { enemies_list::tankers, Color("BLUE", BLUE) }, 
                                                                    { enemies_list::spikers, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::pulsars, Color("YELLOW", YELLOW)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)}};
        
        // const std::map<int, Color> level1_16_characters  =  { { enemies_list::flippers, Color(RED) }, { enemies_list::flippers, Color(RED) }};

        const std::map<int, Color> level17_32_characters  = { { enemies_list::superzapper, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::flippers, Color("PURPLE", PURPLE) }, { enemies_list::tankers, Color("BLUE", BLUE) }, 
                                                                    { enemies_list::spikers, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::pulsars, Color("YELLOW", YELLOW)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)} };

        const std::map<int, Color> level33_48_characters  = { { enemies_list::superzapper, Color("BLUE", BLUE) }, 
                                                                    { enemies_list::flippers, Color("GREEN", GREEN) }, { enemies_list::tankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::spikers, Color("RED", RED) }, { enemies_list::pulsars, Color("BLUE", BLUE)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)} };

        const std::map<int, Color> level49_64_characters  = { { enemies_list::superzapper, Color("RED", RED) }, 
                                                                    { enemies_list::flippers, Color("GREEN", GREEN) }, { enemies_list::tankers, Color("PURPLE", PURPLE) }, 
                                                                    { enemies_list::spikers, Color("RED", RED) }, { enemies_list::pulsars, Color("YELLOW", YELLOW)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)} };

        const std::map<int, Color> level65_80_characters  = { { enemies_list::superzapper, Color("WHITE", WHITE) }, 
                                                                    { enemies_list::flippers, Color("RED", RED) }, { enemies_list::tankers, Color("PURPLE", PURPLE) }, 
                                                                    { enemies_list::spikers, Color("GREEN", GREEN) }, { enemies_list::pulsars, Color("LIGHTBLUE", LIGHT_BLUE)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)} };

        const std::map<int, Color> level81_96_characters  = { { enemies_list::superzapper, Color("PURPLE", PURPLE) }, 
                                                                    { enemies_list::flippers, Color("YELLOW", YELLOW) }, { enemies_list::tankers, Color("PURPLE", PURPLE) }, 
                                                                    { enemies_list::spikers, Color("BLUE", BLUE) }, { enemies_list::pulsars, Color("YELLOW", YELLOW)},
                                                                    { enemies_list::fuseballs, Color("LIGHTBLUE", LIGHT_BLUE) }, { enemies_list::fuseballTankers, Color("LIGHTBLUE", LIGHT_BLUE) }, 
                                                                    { enemies_list::pulsarTankers, Color("YELLOW", YELLOW)} };

        const Color level1_16_map_color { "BLUE", BLUE };
        const Color level17_32_map_color { "RED",  RED };
        const Color level33_48_map_color { "YELLOW",  YELLOW };
        const Color level49_64_map_color { "LIGHTBLUE", LIGHT_BLUE };
        const Color level65_80_map_color { "BLACK", BLACK };
        const Color level81_96_map_color { "GREEN", GREEN };

        const Color level1_16_player_color { "RED",  RED };
        const Color level17_32_player_color { "GREEN", GREEN };
        const Color level33_48_player_color { "BLUE", BLUE };
        const Color level49_64_player_color { "BLUE", BLUE };
        const Color level65_80_player_color { "YELLOW", YELLOW };
        const Color level81_96_player_color { "RED",   RED };

        const Color level1_16_score_color { "GREEN",  GREEN };
        const Color level17_32_score_color { "LIGHTBLUE", LIGHT_BLUE };
        const Color level33_48_score_color { "RED", RED };
        const Color level49_64_score_color { "RED", RED };
        const Color level65_80_score_color { "GREEN", GREEN };
        const Color level81_96_score_color { "PURPLE", PURPLE };

        
};

#endif