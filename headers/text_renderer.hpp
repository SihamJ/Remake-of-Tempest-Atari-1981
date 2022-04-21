#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include <string>
#include <SDL.h>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <memory>
#include "utils.hpp"
#include "Color.hpp"

class TextRenderer
{
    public:
        TextRenderer(){}

        ~TextRenderer(){}

        std::vector<int> parse_score(int value){
            std::vector<int> tmp, res;

            do {
                tmp.push_back(value%10);
                value = value / 10;
            } while(value>0);

            for(auto i  = tmp.rbegin(); i != tmp.rend(); i++)
                res.push_back(*i);

            return res;
        }

        void draw(std::shared_ptr<SDL_Renderer> renderer, int value, int x, int y, std::string color){
            std::string root;

            if(color == "LIGHT_BLUE")
                root = "images/lb";
            else 
                root = "images/s";
            
            std::vector<int> msg = this->parse_score(value);
            int k = 0;
            
            
            for(auto i = msg.begin(); i != msg.end(); i++){

                std::string path = root + std::to_string(*i) + static_cast<std::string>(".bmp");
                
                SDL_Surface* image = SDL_LoadBMP(path.c_str());
                if(!image)
                {
                    SDL_Log("Erreur > %s", SDL_GetError());
                    return;
                }

                SDL_Rect dest_rect = {x, y, 48, 50};
                
                SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer.get(), image);  //La texture monImage contient maintenant l'image importée
                SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface

                if (SDL_QueryTexture(monImage, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0) {
                    SDL_Log("Erreur > %s", SDL_GetError());
                    return;
                }

                dest_rect.w = 30;
                dest_rect.h = 33;
                dest_rect.x = x + (30*(k+1));

                if (SDL_RenderCopyEx(renderer.get(), monImage, NULL, &dest_rect, 0, NULL, SDL_FLIP_NONE) != 0) {
                    SDL_Log("Erreur > %s", SDL_GetError());
                    return;
                }
                k++;
            }
        }


};

#endif