#include "presentacion.h"
    menu.start();
            if (!title.is_enabled()){
                actual = MENU;
                menu.start();
            }
        case MENU:
            menu.update();
            break;

void Presentacion::set_events(SDL_MouseMotionEvent* new_mouse){
    mouse = new_mouse;
    menu.set_events(mouse);
}