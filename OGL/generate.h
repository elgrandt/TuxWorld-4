#ifndef GENERATE_H_
#define GENERATE_H_
#include "includes.h"
#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"

namespace OGL{
    SDL_Surface* create_void_surface(int width,int height);
    SDL_Surface* create_filled_surface(int width,int height,SDL_Color color);
    SDL_Surface* create_circle(SDL_Color color,int radius);
    SDL_Surface* create_filled_circle(SDL_Color color,int radius);
}

#endif
