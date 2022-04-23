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
        void reset_clock(int index);

    private:
        Uint32 start;
        std::vector<Uint32> clocks;

};


#endif