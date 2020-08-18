#include "basic.h"
#include "includes.h"

struct Color;

namespace OGL{
    SDL_Cursor* cursor;
    Color fondo;

    void update_cursor(){
        SDL_SetCursor(cursor);
    }

    void update_background(int r, int g, int b){
        fondo.r = r;
        fondo.g = g;
        fondo.b = b;
    }

    /***** Un puntero a la superficie de la pantalla *****/
    SDL_Surface* screen;
    SDL_Window* display;

    /***** Funcion para setear un pixel de una superficie *****/
    void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel){

        /***** Colores *****/

        Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
        *(Uint32 *)target_pixel = pixel;
    }
    SDL_Color c(int r,int g,int b){
        SDL_Color color;
        color.r = r;
        color.g = g;
        color.b = b;
        return color;
    }
    SDL_Color ac(int r,int g,int b,int a){

        /***** Vistas *****/
        SDL_Color color;
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
        return color;
    }
    void vista_ortografica(int ancho,int alto,int inicio_x,int inicio_y,int specialA, int specialB){
        glOrtho(inicio_x,ancho,inicio_y,alto,specialA,specialB);

    }
}
