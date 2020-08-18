#include <iostream>

#include <vector>
#include <cstdio>
#include <math.h>

#include "lincludes/mSDL.h"
#include "presentacion/presentacion.h"
#include "testing/testing.h"

using namespace std;

void testing_1();
void testing_2();

int main( int argc, char *argv[] ){
    freopen("output.txt","w",stdout);
    load_basic();
    testing_1();
    return 0;
}

void testing_1(){
    Presentacion pres = Presentacion();

    bool continuar = true;
    SDL_MouseMotionEvent mouse = SDL_MouseMotionEvent();
    pres.set_events(&mouse);
    while (continuar){
        while (SDL_PollEvent(&events)){
            switch (events.type){
                case SDL_QUIT:
                    continuar = false;
                    break;
                case SDL_MOUSEMOTION:
                    mouse = events.motion;
                    break;
            }
        }
        pres.update();
        refresh_screen ();
    }
}
