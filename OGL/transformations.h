#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "includes.h"

namespace OGL{
    SDL_Surface* rotate_surface(SDL_Surface* src, double angle);
    SDL_Surface* rotozoom_surface(SDL_Surface* src, double angle, double zoom);
    SDL_Surface* zoom_surface(SDL_Surface* src, double zoomX, double zoomY);
    void add_border(SDL_Surface* input,SDL_Color color);
    void draw_arc(SDL_Surface* surface,double cx, double cy, float r, double start_angle, double arc_angle, int num_segments,int special);
    void border_surface(SDL_Surface* surface, int radius, bool Eiz_ar=true, bool Ede_ar=true, bool Eiz_ab=true, bool Ede_ab=true);
    SDL_Surface* flip_width_surface(SDL_Surface* surface);
    SDL_Surface* rotate_90(SDL_Surface* surface);
}

#endif
