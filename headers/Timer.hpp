#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <SDL.h>
#include <vector>

class Timer {
    public:
        Timer();
        Timer(Uint32 start);
        ~Timer();
        void add_clock();
        Uint32 get_clock(int index);
        Uint32 get_paused_clock(int index);
        void reset_clock(int index);
        void pop_clock();
        void pause_clock(int index);
        void unpause_clock(int index);

    private:
        Uint32 start;
        std::vector<Uint32> clocks;
        std::vector<Uint32> pause;

};


#endif