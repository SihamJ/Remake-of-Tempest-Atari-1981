#ifndef __GAMEOVER_HPP__
#define __GAMEOVER_HPP__

#include "Utils.hpp"
#include "Game.hpp"
#include "TextRenderer.hpp"

class GameOver {
    public:
        GameOver(std::shared_ptr<Game> g);
        ~GameOver();
        void handle_events();
        void update();
        void render();

    private:
        std::shared_ptr<Game> game_ptr;
};


#endif