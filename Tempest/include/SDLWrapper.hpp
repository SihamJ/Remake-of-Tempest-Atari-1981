#ifndef __SDL_WRAPPER_HPP__
#define __SDL_WRAPPER_HPP__

#include <memory>
#include <SDL.h>
#include "Utils.hpp"
#include "Color.hpp"
#include "Point.hpp"


static void SDL_DelRes(SDL_Window   *r) { SDL_DestroyWindow(r);   }
static void SDL_DelRes(SDL_Renderer *r) { SDL_DestroyRenderer(r); }

static void SDL_DelRes(SDL_Texture  *r) { SDL_DestroyTexture(r);  }
static void SDL_DelRes(SDL_Surface  *r) { SDL_FreeSurface(r);     }

template <typename T>
std::shared_ptr<T> sdl_shared(T *t) {
    return std::shared_ptr<T>(t, [](T *t) { SDL_DelRes(t); });
}

template <typename T>
std::unique_ptr<T> sdl_unique(T *t) {
    return std::unique_ptr<T>(t, [](T *t) { SDL_DelRes(t); });
}

const bool render_image(std::shared_ptr<SDL_Renderer> renderer, const std::string path, const int init_width, const int init_height, 
                        const int dest_width, const int dest_height, const int x, const int y, const long double angle, const std::shared_ptr<SDL_Point> center) ;

const bool clear_renderer(std::shared_ptr<SDL_Renderer> renderer, std::string&& color);

void render_present(std::shared_ptr<SDL_Renderer> renderer);

bool init_sdl(Uint32 flags);

std::shared_ptr<SDL_Window> create_window(std::string title, int xpos, int ypos, int flagsWindow);
std::shared_ptr<SDL_Renderer> create_renderer(std::shared_ptr<SDL_Window> window, int index, int flagsRenderer);

void quit_game(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_Renderer> renderer);
void resizeWindow(std::shared_ptr<SDL_Window> window, Uint32 windowWidth, Uint32 windowHeight);
void get_window_size(std::shared_ptr<SDL_Window> window, int *w, int *h);

int set_display(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_DisplayMode> mode);

void render_color(std::shared_ptr<SDL_Renderer> renderer, const Color&& c);
void render_color(std::shared_ptr<SDL_Renderer> renderer, const std::string&& color);
void render_color(std::shared_ptr<SDL_Renderer> renderer, const std::string&& color, const int opacity);


#endif