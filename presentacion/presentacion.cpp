#include "presentacion.h"#include "OGL/OGL.h"#include <cmath>#include <iostream>using namespace std;Presentacion::Presentacion(){    actual = MENU;    vector<string> text_authors;    text_authors.push_back("GranDT & Newtonis");    text_authors.push_back("presentan");    authors.set_text(text_authors);
    menu.start();}void Presentacion::update(){    background.update();    switch (actual) {        case AUTHORS:            authors.update();            if (authors.get_finished()) {                actual = TITLE;                title.enable(&authors);            }            break;        case TITLE:            title.update();
            if (!title.is_enabled()){
                actual = MENU;
                menu.start();
            }            break;
        case MENU:
            menu.update();
            break;        default:            break;    }}

void Presentacion::set_events(SDL_MouseMotionEvent* new_mouse){
    mouse = new_mouse;
    menu.set_events(mouse);
}
