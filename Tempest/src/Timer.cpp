#include "Timer.hpp"

Timer::Timer(){}

Timer::~Timer(){}

void Timer::add_clock(){
    this->clocks.push_back(0);
    this->pause.push_back(0);
}

Uint32 Timer::get_clock(int index){
    return SDL_GetTicks64() - this->clocks.at(index);
}

Uint32 Timer::get_paused_clock(int index){
    return SDL_GetTicks64() - this->pause.at(index);
}

void Timer::pause_clock(int index){
    this->pause.at(index) = SDL_GetTicks64();
}

void Timer::unpause_clock(int index){
    this->clocks.at(index) += get_paused_clock(index);
    this->pause.at(index) = 0;
}

void Timer::reset_clock(int index){
    this->clocks.at(index) = SDL_GetTicks64();
}
