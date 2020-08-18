#include "manager.h"

#include "lincludes/mSDL.h"
#include "timer/timer.h"

#include "utilities.h"
#include "images.h"
#include "gui2/window.h"
#include "playable/stage.h"


/***

/** fingir llamar funciones del mouse
        int mouse_x,mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        mouse_y = 600-mouse_y;
        this->call_mouse_move(mouse_x, mouse_y);
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_MOUSEBUTTONDOWN:
                    this->call_mouse_click(mouse_x, mouse_y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    this->call_mouse_up();
                    break;
            }
        }

***/

Manager::Manager(){
    //ctor
    //SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);


    //window *test_window = new window("Este es el manager", 0,0,400,300);
    //this->add_window_in_center(test_window);

    //calls *test_window = new OGL::button_test("boton");
    //add_element(test_window);


    while (SDL_PollEvent(&event)){}
}
void Manager::handle_update(){
    while (SDL_PollEvent(&event)){
        //if (*start == false){ cout<<"start"<<endl; continue; }
        switch (event.type){
            case SDL_QUIT:
                *continuar = false;
            break;
            case SDL_MOUSEMOTION:
                {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    this->call_mouse_motion(x,y);
                    this->events_status->mouse_x = x;
                    this->events_status->mouse_y = y;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    this->call_mouse_down();
                }
            break;
            case SDL_MOUSEBUTTONUP:
                {
                    this->call_mouse_up();
                }
            break;
            case SDL_WINDOWEVENT:
                OGL::screen = SDL_GetWindowSurface( OGL::display );
                //glMatrixMode(GL_PROJECTION);
                //glLoadIdentity();
                //glOrtho(0,OGL::screen->w,0,OGL::screen->h,-1,1);
            break;

        }
    }

    /*pyfor(windows){     //for (int index = 0;index < windows.size();index++){
        Window* actual;
        pyset(windows,actual); // actual = windows[index]
        //actual->update();
    }*/

    //lvl->update();
}

void Manager::handle_mouse_motion(int x,int y){

}
void Manager::handle_mouse_down(){

}
void Manager::handle_mouse_up(){

}
void Manager::handle_draw(){

}
void Manager::add_window_in_center(window* win){
    int x = OGL::screen->w / 2 - win->rect.w / 2;
    int y = OGL::screen->h / 2 - win->rect.h / 2;

    win->set_position(x,y);

    this->add_element ( (shared::call_element*)win);
}
Manager::~Manager(){
    //dtor
}
