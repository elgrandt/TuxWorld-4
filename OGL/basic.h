#ifndef BASIC_H_
#define BASIC_H_
#include <vector>

#include "includes.h"

using namespace std;

struct Color{
    int r; int g; int b;
};

namespace OGL{
    class Window;

    typedef vector <Window*>* win_container;

    /***** Variables *****/
    extern SDL_Cursor* cursor;
    extern SDL_Window* display;
    extern SDL_Surface* screen;
    extern Color fondo;

    /***** Actualizar forma del cursor *****/
    void update_cursor();
    void update_background(int r, int g, int b);

    /***** Funcion para setear un pixel de una superficie *****/
    void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

    /***** Colores *****/
    SDL_Color c(int r,int g,int b);
    SDL_Color ac(int r,int g,int b,int a);

    /***** Vistas *****/
    void vista_ortografica(int ancho,int alto,int inicio_x = 0,int inicio_y = 0,int specialA = -1, int specialB = -1);
}

#endif
