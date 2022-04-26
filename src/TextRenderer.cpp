#include "../headers/TextRenderer.hpp"


    TextRenderer::TextRenderer(){

    }

    TextRenderer::~TextRenderer(){

    }

    std::vector<int> TextRenderer::parse_score(int value){
        std::vector<int> tmp, res;

        do {
            tmp.push_back(value%10);
            value = value / 10;
        } while(value>0);

        for(auto i  = tmp.rbegin(); i != tmp.rend(); i++)
            res.push_back(*i);

        return res;
    }

    void TextRenderer::draw(std::shared_ptr<SDL_Renderer> renderer, int value, int x, int y, std::string color){
        std::string root;

        if(color == "LIGHT_BLUE")
            root = "images/lb";
        else 
            root = "images/s";
        
        std::vector<int> msg = this->parse_score(value);
        int k = 0;
        
        
        for(auto i = msg.begin(); i != msg.end(); i++){

            std::string path = root + std::to_string(*i) + static_cast<std::string>(".bmp");
            
            auto image = sdl_shared(SDL_LoadBMP(path.c_str()));
            if(!image)
            {
                SDL_Log("Erreur > %s", SDL_GetError());
                return;
            }

            SDL_Rect dest_rect = {x, y, 48, 50};
            
            auto monImage = sdl_shared(SDL_CreateTextureFromSurface(renderer.get(), image.get()));  //La texture monImage contient maintenant l'image importée

            if (SDL_QueryTexture(monImage.get(), NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
                SDL_Log("Erreur > %s", SDL_GetError());
                return;
            }

            dest_rect.w = 30;
            dest_rect.h = 33;
            dest_rect.x = x + (30*(k));

            if (SDL_RenderCopyEx(renderer.get(), monImage.get(), NULL, &dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
                SDL_Log("Erreur > %s", SDL_GetError());
                return;
            }
            k++;
        }
    }


    void TextRenderer::draw_caracter(std::shared_ptr<SDL_Renderer> renderer, char c, int x, int y){
        int index = c - 32;
        std::array<int, 112> element = this->coord.at(index);
        int nb_vertices = element.at(0);
        int hspacing = element.at(1);

        for(int i = 2, j = 0; i < element.size() && j < nb_vertices; i+=2, j++ ){
            if(element.at(i+2) == -1){
                i+=2;
                j++;
                continue;
            }
            Line l{ element.at(i)+x, HEIGHT - element.at(i+1)-y, element.at(i+2)+x,  HEIGHT - element.at(i+3)-y, 1 };
            l.draw(renderer);
        }
    }
    
    void TextRenderer::draw_text(std::shared_ptr<SDL_Renderer> renderer, std::string text, int x, int y){
        int space = 0;
        for(auto i : text){
            this->draw_caracter(renderer, i, x+space, y);
            space += (this->coord.at(i - 32)).at(1);
        }
    }
