#include "window.h"
#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"
#include "OGL/basic.h"
#include "OGL/generate.h"
#include "images.h"
#include "OGL/blits.h"

/***** Crear la superficie de la ventana *****/
SDL_Surface* create_window_surface(int width,int height){ //Atencion, tamaño minimo 200x200
    int global_size = 100;
    SDL_Surface* superficie = OGL::create_void_surface(width,height);
    OGL::blit_surface_inside_another(images::window_images::up::left_window,superficie   ,0                ,0                 );
    OGL::blit_surface_inside_another(images::window_images::down::left_window,superficie ,0                ,height-global_size);
    OGL::blit_surface_inside_another(images::window_images::up::right_window,superficie  ,width-global_size,0                 );
    OGL::blit_surface_inside_another(images::window_images::down::right_window,superficie,width-global_size,height-global_size);
    for (int x = global_size;x < width - global_size;x++){
        OGL::blit_surface_inside_another(images::window_images::up::window,superficie,x,0);
        OGL::blit_surface_inside_another(images::window_images::down::window,superficie,x,height-global_size);

        for (int y = global_size;y < height - global_size;y++){
            if (x == global_size){
                OGL::blit_surface_inside_another(images::window_images::middle::left_window,superficie,0,y);
                OGL::blit_surface_inside_another(images::window_images::middle::right_window,superficie,width-global_size,y);
            }
            OGL::blit_surface_inside_another(images::window_images::middle::window,superficie,x,y);
        }

    }
    return superficie;
}
SDL_Surface* create_top_surface(int width){
    int surface_widthA = images::window_images::redtop::left_window->w;
    int surface_widthB = images::window_images::redtop::right_window->w;

    SDL_Surface* surface = OGL::create_void_surface(width,22);
    OGL::blit_surface_inside_another(images::window_images::redtop::left_window,surface,0,0);
    OGL::blit_surface_inside_another(images::window_images::redtop::right_window,surface,width - surface_widthB,0);

    for (int x = surface_widthA;x < width - surface_widthB;x++){
        OGL::blit_surface_inside_another(images::window_images::redtop::window,surface,x,0);
    }

    return surface;
}


window::window(string mtitle, int x, int y, int w, int h){
    title = mtitle;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    difx = 0;
    dify = 0;
    moving = false;
    y_up = 20;
    espacio_adelante = 46;
    espacio_atras = 72;
    tamanio_minimo_x = 200;
    downrightpressed = false;
    update_surface();
}
void window::update_surface(){
    title_surf = TTF_RenderText_Blended(fonts::bebas_neue_mini, title.c_str(), OGL::c(0,0,0));
    surface = create_window_surface(rect.w,rect.h);
    red_top = create_top_surface(rect.w);
    tamanio_minimo_x = espacio_adelante + title_surf->w + espacio_atras;
}
void window::handle_draw(){
    content_size = rect.h - y_up;
    OGL::blit(surface,rect.x,rect.y,rect.w,rect.h);
    int x_title = espacio_adelante+(rect.w-espacio_adelante-espacio_atras)/2-title_surf->w/2;
    int y_title = y_up/2-title_surf->h/2;
    pos_buttons[0].x = rect.x+rect.w-17;
    pos_buttons[0].y = rect.y+rect.h-17;
    pos_buttons[0].w = 25;
    pos_buttons[0].h = 12;
    
    if (cross_focused()){
        OGL::blit(red_top,rect.x,rect.y+rect.h-22,rect.w,22);
        OGL::cursor = cursors::close;
    }
    
    if (moving){
        OGL::cursor = cursors::hand;
    }else if(downrightpressed){
        OGL::cursor = cursors::downright;
        int nw = px - (- events_status->mouse_x + mxx);
        int nh = py - (- events_status->mouse_y + myy);
        int ny = (-  + yy + myy);
        if (nw <= tamanio_minimo_x){ nw = tamanio_minimo_x+1; }
        if (nh <= 200){ ny += nh-201; nh = 201;}
        rect.y = ny;
        rect.w = nw;
        rect.h = nh;

        SDL_FreeSurface(title_surf);
        SDL_FreeSurface(surface);
        SDL_FreeSurface(red_top);
        update_surface();
    }
    
    OGL::blit(title_surf,rect.x+x_title,rect.y+content_size+y_title);
}

void window::handle_mouse_motion(int x, int y){
    if (moving){
        int nx = x-this->difx;
        int ny = (OGL::screen->h - y)-this->dify;
        
        rect.x = nx;
        rect.y = ny;
    }
}
void window::handle_mouse_down(){
    int mx = events_status->mouse_x;
    int my = OGL::screen->h - events_status->mouse_y;

    if ( cross_focused() ){
        this->kill();
    }
    if (mx > rect.x and mx < rect.x+rect.w && my > rect.y+this->content_size && my < rect.y + rect.h) {
        if (not this->cross_focused()){
            this->moving = true;
            this->difx = mx-rect.x;
            this->dify = my-rect.y;
        }
    }
    if (right_down_focused()){
        downrightpressed = true;
        px = rect.w;
        py = rect.h;
        mxx = events_status->mouse_x;
        myy = events_status->mouse_y;
        yy = rect.y;
    }
}
void window::handle_mouse_up(){
    moving = false;
    downrightpressed = false;
}
void window::handle_update(){
}
bool window::cross_focused(){
    int mx = events_status->mouse_x; int my = OGL::screen->h  - events_status->mouse_y;
    shared::square act = pos_buttons[0];
    
    if (mx > act.x and mx < act.x+act.w){
        if (my > act.y and my < act.y+act.h){
            return true;
        }
    }
    return false;
}
bool window::green_focused(){
    return 0;
}
bool window::yellow_focused(){
    return 0;
}
bool window::blue_focused(){
    return 0;
}
bool window::right_down_focused(){
    int mx = events_status->mouse_x; int my = OGL::screen->h  - events_status->mouse_y;
    return mx >= rect.x + rect.w - 5 and mx <= mx + rect.w and my >= rect.y and my <= rect.y+5;
}
void window::set_position(int x, int y){
    this->rect.x = x;
    this->rect.y = y;
}
window::~window()
{
    //dtor
}
