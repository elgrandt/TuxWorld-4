#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "OGL/generate.h"
#include "OGL/blits.h"
#include "lincludes/mSDL.h"
#include "global.h"
#include "images.h"

using namespace std;


SDL_Surface* create_window_surface(int width,int height);
SDL_Surface* create_top_surface(int width);


class window : public shared::call_element_container{
    private:

        shared::square pos_buttons[4];
        SDL_Surface* surface;
        SDL_Surface* title_surf;
        SDL_Surface* red_top;
        string title;

        bool moving;
        int difx;
        int dify;
        bool downrightpressed;

        int px;
        int py;
        int yy;
        int mxx;
        int myy;
        int y_up;
        int espacio_adelante;
        int espacio_atras;
        int tamanio_minimo_x;
        int content_size;

    public:
        shared::square rect;

        window(string title,int x,int y,int w,int h);
        virtual ~window();

        void update_surface();

        bool cross_focused();
        bool green_focused();
        bool yellow_focused();
        bool blue_focused();
        bool right_down_focused();

        void handle_mouse_motion(int x,int y);
        void handle_mouse_down();
        void handle_mouse_up();
        void handle_update();
        void handle_draw();
        void set_position(int x,int y);


    protected:

};

#endif // WINDOW_H
