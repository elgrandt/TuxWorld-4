#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include <iostream>
#include <math.h>

#include "lincludes/mSDL.h"
#include "lincludes/mSDL_image.h"

#include "timer/timer.h"
#include "manager.h"

using namespace std;


class Graphical{
    private:
        SDL_Window* display;
        SDL_Renderer* renderer;
        SDL_GLContext context_general;
        Manager* managment;
        LTimer* mytimer;
        int* mycounter;
        int w;
        int h;
    public:
        Graphical(int w,int h);
        void start();
        void set_logic_manager(Manager* manager);
        void update_graphics();
        void updating();
        void set_tick_setter(LTimer* timer,int* counter);
        virtual ~Graphical();
        void update_fps();
        void handle_mousemotion(int x,int y);
        void handle_mousedown();
        void handle_mouseup();
};

#endif // GRAPHICAL_H
