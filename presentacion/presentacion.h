#ifndef PRESENTACION_H_
#define PRESENTACION_H_

#define AUTHORS 0
#define TITLE   1
#define MENU    2

#include "lincludes/mSDL.h"
#include "background.h"
#include "authors.h"
#include "title.h"
#include "menu.h"

class Presentacion{
    private:
        Background background;
        Authors authors;
        Title title;
        Menu menu;
        int actual;
        SDL_MouseMotionEvent* mouse;
    public:
        Presentacion();
        void update();
        void set_events(SDL_MouseMotionEvent* new_mouse);
};

#endif
