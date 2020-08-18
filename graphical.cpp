#include <string>
#include <sstream>
#include <cstdio>

#include "graphical.h"
#include "images.h"
#include "OGL/OGL.h"
#include "playable/stage.h"

#include "lincludes/mOPENGL.h"
#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"

#define PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841

#include "images.h"



void Graphical::update_fps(){
    int fps = (*mycounter) / ( mytimer->getTicks() / 1000.f );
    stringstream ss; ss << fps;
    OGL::blit_text(fonts::bebas_neue,ss.str().c_str(),OGL::c(0,0,0),OGL::screen->w-40,OGL::screen->h-30);
}


Graphical::Graphical(int w,int h){
    this->w = w;
    this->h = h;
    start();
}

void Graphical::start(){
    /***** inicializamos SDL y OPENGL *****/
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    display = SDL_CreateWindow("Tux world 32",0,50,w,h,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    OGL::screen = SDL_GetWindowSurface( display);
    OGL::display = display;
    context_general = SDL_GL_CreateContext(display);

    /***** Cargamos imagenes *****/
    load();

    SDL_GL_SetSwapInterval(1);

    /***** Blanqueamos la pantalla *****/
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    /***** Seteamos la vista de OPENGL *****/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,800,0,600,-1,1);

}

void Graphical::update_graphics(){
    /***** Blanqueamos la pantalla *****/
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(255,0,0,0);
    /***** actualizamos los graficos *****/
    updating();

    /***** Funciones de opengl/sdl para actualizar *****/
    //SDL_RenderPresent(renderer);
    SDL_GL_SwapWindow(display);

}

void Graphical::updating(){
    /*pyfor(managment->lvl->container){
        epointer actual;
        pyset(managment->lvl->container,actual);

        OGL::blit(images::img[actual->get_image()],actual->get_x(),actual->get_y());
    }*/

    OGL::cursor = cursors::cursor;

    for (int x = 0;x < managment->get_into()->size();x++){
        shared::events_call_functions* actual = managment->get_into()->at(x);
        actual->call_draw();
    }


    update_fps();
    OGL::update_cursor();
}

void Graphical::set_logic_manager(Manager* manager){
    managment = manager;
}

void Graphical::set_tick_setter(LTimer* timer,int* counter){
    mytimer  = timer;//SDL_SetCursor(cursors::cursor);
    //OGL::cursor = cursors::cursor;

    mycounter = counter;
}

Graphical::~Graphical(){
    //dtor
}
void Graphical::handle_mousedown(){

}
void Graphical::handle_mouseup(){
}
void Graphical::handle_mousemotion(int x,int y){
}

