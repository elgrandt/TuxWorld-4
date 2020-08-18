#include "menu.h"
#include <iostream>
#include "OGL/OGL.h"
using namespace std;

bool BotonMenu::hover(int X, int Y){
    return X > x && X < x+w && Y > y && Y < y+h;
}

void BotonMenu::generate_texture(){

}

void Menu::start(){
    string buttons[] = {"Boton 1","Boton 2","Boton 3","Boton 4"};
    int botones_size = 4;
    int defaultW = 200, defaultH = 50, separacion = 2;
    int y_act = OGL::screen->h/2 - ((botones_size*(defaultH+separacion)) - separacion)/2;
    for (int x = 0; x < botones_size; x++){
        BotonMenu boton_act;
        boton_act.w = defaultW;
        boton_act.h = defaultH;
        boton_act.x = OGL::screen->w/2 - boton_act.w/2;
        boton_act.y =  y_act;
        boton_act.color = OGL::c(60,148,255);
        boton_act.generate_texture();
        boton_act.title = buttons[x];
        botones.push_back(boton_act);
        y_act += boton_act.h+separacion;
    }
}

void Menu::update(){
    for (int x = 0; x < botones.size(); x++){
        OGL::blit_texture(botones[x].texture,botones[x].x,botones[x].y,botones[x].w,botones[x].h);

    }
}

void Menu::set_events(SDL_MouseMotionEvent* new_mouse){
    mouse = new_mouse;
}
