#include "stage.h"
#include "elements/player.h"
#include "elements/wall.h"
#include "elements/tecnowall.h"
#include "elements/background.h"

#include "OGL/OGL.h"
#include "images.h"


#define NOSET -1

Stage::Stage(){

}


void Stage::add_player (int position_x, int position_y, Handler *controller){
    player *new_player = new player();
    new_player->set_x ( position_x );
    new_player->set_y ( position_y );
    controller->set_player (new_player);
    new_player->set_controller(controller);

    this->add_element ( new_player );
    this->level_players.push_back (controller);
}

void Stage::add_element(epointer adding){
    //Tecnowall* act;
    //if (adding->type == TECNOWALL) {
    //    act = (Tecnowall*)adding;
    //    cout<<act->paredes[0]->x<<endl;
    //}


    adding->initializate ( this );
    container.push_back(adding);
    types[adding->type].push_back (adding);

    //if (adding->type == TECNOWALL) {
    //    cout<<act->paredes[0]->x<<endl;
    //}
}

void Stage::remove_element(Element* remove){
    for (int x = 0;x < (signed)container.size();x++){
        if (container[x] == remove){
            delete remove;
            container.erase(container.begin()+x);
            return;
        }
    }
}

void Stage::check_delete(){
    for (int x = container.size()-1;x > -1;x--){
        if (!container[x]->is_on()){
            delete container[x];
            container.erase(container.begin()+x);
        }
    }
}

void Stage::update(){
    pyfor(container){
        epointer actual;
        pyset(container,actual);
        actual->update ();
    }
    pyfor(level_players){
        Handler *actual;
        pyset(level_players,actual);
        actual->take_action ();
    }
}

void Stage::save_check_point(double xpoint,double ypoint){
    check_point_x = xpoint; check_point_y = ypoint;
}
graphic_stage::graphic_stage() : Stage(){
    focus = NOSET;
    camera_x = 400;
    camera_y = 300;
}

void graphic_stage::draw (){

    update_camera ();

    for (int v = 0;v < AMOUNT_TYPES;v++){
        draw_layer(v);
    }
    update_camera();
}
void graphic_stage::draw_layer(int layer){
    update_screener();
    pyfor(types[layer]){
        epointer actual; pyset(types[layer],actual);
        if (not actual->checkdraw ()){
            continue;
        }
        switch(actual->get_type ()){
            case TECNOWALL:
                {
                    Tecnowall* act = (Tecnowall*)actual;
                    act->update_graphics();
                }
            break;
            case MULTI_IMAGES:
                {
                    ElementWIMG* elimages = (ElementWIMG*)actual;
                    for (int x = 0;x < elimages->get_images().size();x++){
                        OGL::blit_texture ( elimages->get_images()[x].image , elimages->get_x() + elimages->get_images()[x].x , elimages->get_y() + elimages->get_images()[x].y , elimages->get_images()[x].w , elimages->get_images()[x].h , 1 , 1 );
                    }
                }
            break;
            default:
                {
                    OGL::blit_texture ( actual->get_image (), actual->get_x () , actual->get_y () ,actual->get_w (),actual->get_h () , actual->get_rx () ,actual->get_ry ());
                }
            break;
        }
    }
}

void graphic_stage::set_focus_player (int ID){
    focus = ID;
    zoom = 1;
}
void graphic_stage::update_camera (){
    if (focus == NOSET){ return; }

    player* now_is = level_players[focus]->get_central();

    int x_is = now_is->get_x();
    int y_is = now_is->get_y();

    if (x_is + 100 < camera_x){
        camera_x -= 3;
    }
    if (x_is - 100 > camera_x){
        camera_x += 3;
    }
    if (y_is + 100 < camera_y){
        camera_y -= 3;
    }
    if (y_is - 100 > camera_y){
        camera_y += 3;
    }

    int start_x = camera_x - 400;
    int start_y = camera_y - 300;
    int end_x   = camera_x + 400;
    int end_y   = camera_y + 300;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(start_x, end_x, start_y, end_y, -1, 1);

}

void graphic_stage::set_zoom(double factor){
    zoom = factor;
}
void graphic_stage::sum_zoom (double value){

    if (not (zoom + value < 0.1) and not (zoom + value > 2)){
        zoom += value;
    }
}
void graphic_stage::update_screener(){
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, OGL::screen->w, 0, OGL::screen->h, -1, 1);
    glViewport (0,0,800,600);

    for (int x = 0;x < level_players.size();x++){
        OGL::blit_texture(level_players[x]->get_surface_name(),OGL::screen->w-85,OGL::screen->h-25,80,20);
        int energy = level_players[x]->get_energy();
        int xv = OGL::screen->w - 85;
        int yv = OGL::screen->h - 40;
        int w = 80;
        int h = 10;

        glBegin(GL_QUADS);
        if (energy >= 8){
            glColor3ub (100,255,100);
        }else if(energy >= 4){
            glColor3ub (255,100,0);
        }else{
            glColor3ub (255,0,0);
        }
        glTexCoord2f(   0,   0 );  glVertex2f(xv              ,  yv );
        glTexCoord2f(   1,   0 );  glVertex2f(xv + w*energy/10,  yv );
        glTexCoord2f(   1,  -1 );  glVertex2f(xv + w*energy/10,  yv + h);
        glTexCoord2f(   0,  -1 );  glVertex2f(xv              ,  yv + h);
        glEnd();
        glColor3ub (255,255,255);


        OGL::blit_texture(level_players[x]->get_surface_money(),OGL::screen->w - 65,OGL::screen->h-60,40,20);
    }

    glPopMatrix();
}






