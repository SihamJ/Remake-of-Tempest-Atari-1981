#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "Utils.hpp"
#include "Game.hpp"
#include "TextRenderer.hpp"



class Menu {
    public:
        Menu(std::shared_ptr<Game> g);
        ~Menu();
        void handle_events();
        void update();
        void render();

    private:
        std::shared_ptr<Game> game_ptr;
        int chosen_level = 0;
};


#endif