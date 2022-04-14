#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define RED "255000000"
#define WHITE "255255255"
#define BLACK "000000000"
#define LIGHT_BLUE "000255255"
#define YELLOW "255255000"
#define BLUE "000000255"
#define GREEN "000255000"
#define PURPLE "220000220"

// TO DO: this enum is not used yet. To respect modern c++ conventions, it would be better to switch from #define to enum and writing a converter from hexa to rgb
enum color  { red = 0XFF0000,  white = 0XFFFFFF, black = 0X000000, light_blue = 0X00FFFF, yellow = 0XFFFF00 };

#define TICK 100

// width and height of our window
#define WIDTH 1200
#define HEIGHT 800


enum enemies_list {
    flippers = 0, tankers = 1, spikers = 2, superzapper = 3, pulsars = 4, fuseballs = 5
};

enum maps_list {
    circle = 0, square = 1, plussymbol = 2, blowtie = 3, stylizedcross = 4, triangle = 5, clover = 6, v = 7, steps = 8, u = 9, 
    completelyflat= 10, heart = 11, star = 12, w = 13, fan = 14, infinitysymbol = 15
};

#endif
