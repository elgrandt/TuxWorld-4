#ifndef MANAGER_H
#define MANAGER_H

#include <vector>

#include "lincludes/mSDL.h"

#include "OGL/OGL.h"
#include "gui2/global.h"
#include "gui2/window.h"
#include "playable/stage.h"

using namespace std;
using namespace OGL;

struct Manager : public shared::call_element_container{
    SDL_Event event;

    Stage* lvl;
    bool* continuar;
    int* counter;
    bool* start;

    Manager();

    void handle_mouse_motion(int x,int y);
    void handle_mouse_down();
    void handle_mouse_up();
    void handle_update();
    void handle_draw();
    void add_window_in_center(window* element);
    virtual ~Manager();
};

#endif // MANAGER_H
