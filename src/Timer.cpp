#include "../headers/Timer.hpp"

Timer::Timer(){}

Timer::~Timer(){}

void Timer::add_clock(){
    this->clocks.push_back(0);
}

Uint32 Timer::get_clock(int index){
    return SDL_GetTicks64() - this->clocks.at(index);
}

void Timer::reset_clock(int index){
    this->clocks.at(index) = SDL_GetTicks64();
}