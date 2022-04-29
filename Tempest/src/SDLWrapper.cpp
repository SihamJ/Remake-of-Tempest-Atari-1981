#include "SDLWrapper.hpp"

extern int WIDTH;
extern int HEIGHT;

const bool render_image(std::shared_ptr<SDL_Renderer> renderer, const std::string path, const int init_width, const int init_height, const int dest_width, 
                        const int dest_height, const int x, const  int y, const long double angle, const std::shared_ptr<SDL_Point> center) {

    auto image = sdl_shared(SDL_LoadBMP(path.c_str()));
    auto surface = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));

    SDL_Rect dest_rect = {0, 0, init_width, init_height};

    if (SDL_QueryTexture(surface.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return true;
    }

    dest_rect.w = dest_width;
    dest_rect.h = dest_height;
    dest_rect.x = x;
    dest_rect.y = y;

    if (SDL_RenderCopyEx(renderer.get(), surface.get(), NULL, &dest_rect, angle, center.get(), SDL_FLIP_NONE) != 0) {
        SDL_Log("Erreur > %s", SDL_GetError());
        return true;
    }
    
    return false;

}

const bool clear_renderer(std::shared_ptr<SDL_Renderer> renderer, std::string&& color){

    std::string name = color;
    Color c = Color(std::move(name), std::move(color));

    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), c.get_a());

    if (SDL_RenderClear(renderer.get()) < 0) {
        std::cerr<<"Pb render clear SDL"<< std::endl;
        return true;
    }
    return false;
}

void render_present(std::shared_ptr<SDL_Renderer> renderer){
    SDL_RenderPresent(renderer.get());
}

bool init_sdl(Uint32 flags){
    return SDL_Init(flags);
}

std::shared_ptr<SDL_Window> create_window(std::string title, int xpos, int ypos, int flagsWindow){
    return sdl_shared<SDL_Window>(SDL_CreateWindow(title.c_str(), xpos, ypos, WIDTH, HEIGHT, flagsWindow));
}

std::shared_ptr<SDL_Renderer> create_renderer(std::shared_ptr<SDL_Window> window, int index, int flagsRenderer){
    return sdl_shared(SDL_CreateRenderer(window.get(), -1, flagsRenderer));
}

void resizeWindow(std::shared_ptr<SDL_Window> window, Uint32 windowWidth, Uint32 windowHeight) {
    SDL_SetWindowSize(window.get(), windowWidth, windowHeight);
    WIDTH = windowWidth;
    HEIGHT = windowHeight;
}

void get_window_size(std::shared_ptr<SDL_Window> window, int *w, int *h){
    SDL_GetWindowSize(window.get(), w, h);
}

int set_display(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_DisplayMode> mode){
    return SDL_SetWindowDisplayMode(window.get(), mode.get());
}

void quit_game(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_Renderer> renderer){
    SDL_DestroyWindow(window.get());
    SDL_DestroyRenderer(renderer.get());
    SDL_Quit();
}


void render_color(std::shared_ptr<SDL_Renderer> renderer, Color&& c){
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), c.get_a());
}

void render_color(std::shared_ptr<SDL_Renderer> renderer, std::string&& color){
    Color c { "", std::move(color) };
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), 255);
}

void render_color(std::shared_ptr<SDL_Renderer> renderer, std::string&& color, const int opacity){
    Color c { "", std::move(color), opacity };
    SDL_SetRenderDrawColor(renderer.get(), c.get_r(), c.get_g(), c.get_b(), opacity);
}
