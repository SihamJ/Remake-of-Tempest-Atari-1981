#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Tube.hpp"
#include "Enemy.hpp"
#include "TriangleMap.hpp"
#include "Flippers.hpp"
#include "Spikers.hpp"
#include "utils.hpp"
#include "Color.hpp"

class Level {
    public:
        Level();
        ~Level();

        std::shared_ptr<Tube> get_map();
        int get_current_level();
        std::map<int, Color> get_enemies();
        Color get_player_color();
        Color get_map_color();
        const int get_nb_enemies();
        void next_level();
        std::shared_ptr<Enemy> new_enemy();
        void print();

    private:
        void set_map();
        void set_enemies();
        void set_player_color();
        void set_current_level(int level);
        int current_level = 0;
        std::shared_ptr<Tube> map;
        std::map<int, Color> current_enemies;
        Color current_player_color;


        // description des différents niveaux, leurs ennemies, map et couleurs.
        // Il n'y a qu'une seule instance de Level dans ce jeu, qui se met à jour au fur et à mesure que le joueur progresse,
        // et récupère les variables statiques ci-dessous pour construire la scène

        const std::map<int, Color> level1_16_characters  =  { { enemies_list::superzapper, Color(YELLOW) }, 
                                                                    { enemies_list::flippers, Color(RED) }, { enemies_list::tankers, Color(BLUE) }, 
                                                                    { enemies_list::spikers, Color(LIGHT_BLUE) } };
        
        // const std::map<int, Color> level1_16_characters  =  { { enemies_list::flippers, Color(RED) }, { enemies_list::flippers, Color(RED) }};

        const std::map<int, Color> level17_32_characters  = { { enemies_list::superzapper, Color(LIGHT_BLUE) }, 
                                                                    { enemies_list::flippers, Color(PURPLE) }, { enemies_list::tankers, Color(BLUE) }, 
                                                                    { enemies_list::spikers, Color(LIGHT_BLUE) }, { enemies_list::pulsars, Color(YELLOW)} };

        const std::map<int, Color> level33_48_characters  = { { enemies_list::superzapper, Color(BLUE) }, 
                                                                    { enemies_list::flippers, Color(GREEN) }, { enemies_list::tankers, Color(LIGHT_BLUE) }, 
                                                                    { enemies_list::spikers, Color(RED) }, { enemies_list::pulsars, Color(BLUE)} };

        const std::map<int, Color> level49_64_characters  = { { enemies_list::superzapper, Color(RED) }, 
                                                                    { enemies_list::flippers, Color(GREEN) }, { enemies_list::tankers, Color(PURPLE) }, 
                                                                    { enemies_list::spikers, Color(RED) }, { enemies_list::pulsars, Color(YELLOW)} };

        const std::map<int, Color> level65_80_characters  = { { enemies_list::superzapper, Color(WHITE) }, 
                                                                    { enemies_list::flippers, Color(RED) }, { enemies_list::tankers, Color(PURPLE) }, 
                                                                    { enemies_list::spikers, Color(GREEN) }, { enemies_list::pulsars, Color(LIGHT_BLUE)} };

        const std::map<int, Color> level81_96_characters  = { { enemies_list::superzapper, Color(PURPLE) }, 
                                                                    { enemies_list::flippers, Color(YELLOW) }, { enemies_list::tankers, Color(PURPLE) }, 
                                                                    { enemies_list::spikers, Color(BLUE) }, { enemies_list::pulsars, Color(YELLOW)} };
        const Color level1_16_map_color { BLUE };
        const Color level17_32_map_color { RED };
        const Color level33_48_map_color { YELLOW };
        const Color level49_64_map_color { LIGHT_BLUE };
        const Color level65_80_map_color { BLACK };
        const Color level81_96_map_color { GREEN };

        const Color level1_16_player_color { RED };
        const Color level17_32_player_color { GREEN };
        const Color level33_48_player_color { BLUE };
        const Color level49_64_player_color { BLUE };
        const Color level65_80_player_color { YELLOW };
        const Color level81_96_player_color { RED };

        
};

#endif