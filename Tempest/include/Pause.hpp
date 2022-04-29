#ifndef __PAUSE_HPP__
#define __PAUSE_HPP__

#include "Utils.hpp"
#include "Game.hpp"
#include "TextRenderer.hpp"
#include "Player.hpp"

class Pause {
    public:
        Pause(std::shared_ptr<Game> g);
        ~Pause();
        void handle_events();
        void update();
        void render();

    private:
        std::shared_ptr<Game> game_ptr;
};


#endif