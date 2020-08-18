#include <string>
#include <sstream>

#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"
#include "lincludes/mOPENGL.h"

#include "timer/timer.h"

#include "testing.h"
#include "OGL/OGL.h"

#include "images.h"

using namespace std;

SDL_Window* window;
SDL_GLContext scontext;
SDL_Surface* screen;
string testing_name;
SDL_Event events;
LTimer timer;
LTimer cap_timer;

int counter;

int width         = 800;
int height        = 600;
double fpscontrol = 100;


void update_fps(){
    cap_timer.start ();

    int fps = (counter) / ( timer.getTicks() / 1000.f );
    if (fps > 2000000){
        fps = 0;
    }
    stringstream ss; ss << fps;
    OGL::blit_text(fonts::bebas_neue,ss.str().c_str(),OGL::c(0,0,0),10,height-30);

    int ticks = cap_timer.getTicks ();
    if (ticks < fpscontrol){
        SDL_Delay ( 1000/fpscontrol - ticks );
    }
    counter ++;
}

void start_testing(string tn){
    counter = 0;
    timer = LTimer();
    cap_timer = LTimer();
    cap_timer.start ();
    timer.start ();

    testing_name = tn;
    SDL_SetWindowTitle (window , tn.c_str ());
}

void load_basic(){
    OGL::update_background(0,0,0);

    window = SDL_CreateWindow (testing_name.c_str (),100,100,width,height,SDL_WINDOW_OPENGL);

    screen = SDL_GetWindowSurface(window);

    OGL::screen = screen;
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    scontext = SDL_GL_CreateContext(window);
    //return;
    SDL_GL_SetSwapInterval(1);

    load();

    /***** Blanqueamos la pantalla *****/
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    /***** Seteamos la vista de OPENGL *****/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glViewport (0,0,800,600);

}

void refresh_screen(){

    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glViewport (0,0,800,600);
    update_fps();

    glPopMatrix();
    SDL_GL_SwapWindow(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Color bac = OGL::fondo;
    glClearColor(bac.r/255.0,bac.g/255.0,bac.b/255.0,1.0);

}

/*
SDL_GetWindowSurface( display);
    OGL::display = display;
    context_general = SDL_GL_CreateContext(display);
*/
