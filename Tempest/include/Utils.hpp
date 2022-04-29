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

#define GLOW "095085085"

#define PI 3.141592653589793238463

// 12 second for each level
#define LEVEL_TIME 12000
// 2 seconds for transistion
#define TRANSISTION_TIME 2000
// superzapper time = 1s
#define SUPERZAPPER_TIME 1000
// points de vie au début du jeu
#define INIT_VIE 5

// TO DO: this enum is not used yet. To respect modern c++ conventions, it would be better to switch from #define to enum and writing a converter from hexa to rgb
enum color  { red = 0XFF0000,  white = 0XFFFFFF, black = 0X000000, light_blue = 0X00FFFF, yellow = 0XFFFF00 };

#define TICK 100

// width and height of our window
static int WIDTH = 1400;
static int HEIGHT = 800;



enum enemies_list {
    flippers = 0, tankers = 1, spikers = 2, pulsars = 3, fuseballs = 4, fuseballTankers = 5, pulsarTankers = 6
};

enum maps_list {
    circle = 0, square = 1, plussymbol = 2, blowtie = 3, stylizedcross = 4, triangle = 5, clover = 6, v = 7, steps = 8, u = 9, 
    completelyflat= 10, heart = 11, star = 12, w = 13, fan = 14, infinitysymbol = 15
};

enum clock_list{
    update = 0, enemies = 1, level = 2, current_transition = 3
};

#endif
