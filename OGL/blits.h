#ifndef BLITS_H_
#define BLITS_H_
#include "includes.h"
#include "lincludes/mOPENGL.h"
using namespace std;

namespace OGL{
    void dibujar_cuadrado(int ancho,int alto,int x,int y,SDL_Color color);
    GLuint generate_texture(SDL_Surface* surface);
    void blit_texture(GLuint texture,int x,int y,int w,int h, int rx=1,int ry=1);
    void blit_texture_rotated(GLuint texture, int x, int y, int w, int h, int angle);
    void simple_blit(SDL_Surface* surface,int x,int y);
    void blit(SDL_Surface* surface,int x,int y, double angle = 0, int w = NO_NUMBER, int h = NO_NUMBER);
    void gl_blit_texture(GLuint texture, int x, int y, int w, int h);
    void blit_text(TTF_Font* font, string text, SDL_Color color, int x, int y);
    void blit_surface_inside_another(SDL_Surface* source, SDL_Surface* destination, int x, int y);
    SDL_Surface* repeat_surface(SDL_Surface* root,int ax,int ay);
}

#endif
