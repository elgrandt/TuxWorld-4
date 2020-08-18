#include <iostream>

#include <vector>
#include <cstdio>

#include "lincludes/mSDL.h"

#include "timer/timer.h"

#include "element.h"
#include "playable/stage.h"


#include "graphical.h"
#include "manager.h"
#include "testing/testing.h"
#include "OGL/OGL.h"


bool main_game() {

    //freopen("archivo.out","w",stdout);


    Stage stage = Stage();

    Graphical graphical = Graphical(800,600);

    LTimer timer;
    int counter = 0;
    bool start = false;

    timer.start();

    Manager manager;
    manager.lvl = &stage;
    graphical.set_logic_manager(&manager);
    graphical.set_tick_setter(&timer,&counter);


    /*
    epointer r = (epointer)(new Root());
    r->set_x(10);
    r->set_y(100);
    r->set_w(100);
    r->set_h(200);
    stage.add_element(r,DEFAULT);

    epointer r2 = (epointer)(new Root());
    r2->set_x(100);
    r2->set_y(400);
    r2->set_w(50);
    r2->set_h(50);
    stage.add_element(r2,DEFAULT);
    */

    bool continuar = true;

    manager.continuar = &continuar;
    manager.counter = &counter;
    manager.start = &start;


    while (continuar){
        graphical.update_graphics();
        manager.call_update();
        counter++;
        start = true;
    }
    return 0;
}
