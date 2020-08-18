#include <iostream>

#include "player.h"
#include "element.h"
#include "images.h"
#include "playable/stage.h"
#include "playable/collision.h"
#include "playable/handler.h"
#include "playable/elements/money.h"
#include "playable/elements/enemy.h"
#include "playable/elements/tecnowall.h"
#include "playable/elements/check_point.h"

using namespace std;

player::player() : Element(){
    //ctor
    set_image( images::tux[0].img );
    this->set_w(64*0.75);
    this->set_h(100*0.75);

    speed = 3;
    going_up    = false;
    going_down  = false;
    going_left  = false;
    going_right = false;
    loops       = 0;
    this->add_tag ( TAG_PLAYER );
    this->set_type ( PLAYER );

    for (int x = 0;x < 4;x++) {
        act_coll[x] = 0;
    }
    obtained = false;
    timeout  = 0;
}

player::~player(){
    //dtor
}
void player::move_up(){
    get_collision();
    if (act_coll[coll::down]){
        return;
    }
    going_up = true;
    this->sum_y(+this->speed);

}
void player::move_down(){
    get_collision();

    if (act_coll[coll::up]){
        return;
    }

    going_down = true;
    this->sum_y(-this->speed);
}
void player::move_left(){
    get_collision();

    if (act_coll[coll::left]){
        return;
    }

    going_left = true;
    this->sum_x(-this->speed);
}
void player::move_right(){
    get_collision();

    if (act_coll[coll::right]){
        return;
    }

    going_right = true;
    this->sum_x(+this->speed);
}
void player::update(){

    obtained = false;

    if (going_left and not going_right){
        this->set_image ( images::tux_caminando_costado_b[ loops/10 % images::tux_caminando_costado_b.size () ].img );
    }else if(going_right and not going_left){
        this->set_image ( images::tux_caminando_costado[ loops/10 % images::tux_caminando_costado.size () ].img);
    }else if (going_up and not going_down){
        this->set_image ( images::tux_arriba[ loops/10 % images::tux_arriba.size() ].img);
    }else if(going_down and not going_up){
        this->set_image ( images::tux[ loops/10 % images::tux.size () ].img);
    }else{
        this->set_image ( images::tux[0].img);
    }

    loops ++;
    reset_going ();

    if (timeout > 0){
        //cout<<timeout<<endl;
        timeout --;
        if (timeout % 20 < 10){
            this->enabledraw();
        }else{
            this->disabledraw();
        }
    }
}
void player::reset_going (){
    going_up    = false;
    going_down  = false;
    going_left  = false;
    going_right = false;
}
void player::get_collision (){

    if (this->obtained){ return; }
    bool new_coll[4];
    for (int v = 0;v < 4;v++){ new_coll[v] = 0; }


    for (int id = 0;id < this->outside->container.size ();id++){
        epointer element = this->outside->container[id];
        if (element->tags[TAG_WALL] and element != this){
            collist hap = collide(this,element);
            for (int c = 0;c < hap.size ();c++){
                collision actual = hap[c];
                new_coll [ actual.side ] = 1;
            }
        }
    }
    for (int id = 0;id < this->outside->types[CASH].size ();id++){
        collist hap = collide(this,this->outside->types[CASH][id]);
        if (hap.size () > 0){
            Money* el = (Money*)(this->outside->types[CASH][id]);
            double money = el->get_value();
            this->controller->give_money ( money );
            this->outside->types[CASH][id]->kill();
        }
    }
    for (int id = 0;id < this->outside->types[TECNOWALL].size();id++){
        Tecnowall* tecno = (Tecnowall*)this->outside->types[TECNOWALL][id];
        for (int w = 0;w < tecno->act_wall;w++){
            AdvancedWall *ad = &tecno->walls[w];
            Root t = Root();
            t.set_x (ad->x);
            t.set_y (ad->y);
            t.set_w (ad->cx*ad->img.w);
            t.set_h (ad->cy*ad->img.h);

            collist hap = collide(this,&t);
            for (int c = 0;c < hap.size ();c++){
                collision actual = hap[c];
                new_coll [ actual.side ] = 1;
            }

        }
    }
    for (int id = 0;id < this->outside->types[CHECK_POINT].size();id++){
        collist hap = collide(this,this->outside->types[CHECK_POINT][id]);
        if (hap.size () > 0){
            check_point* el = (check_point*)(this->outside->types[CHECK_POINT][id]);
            el->tick ();
        }
    }
    /*for (int id = 0;id < this->outside->types[ENEMY].size();id++){
        collist hap = collide(this,this->outside->types[ENEMY][id]);
        if (hap.size () > 0){
            //this->timeout = 100;
        }
    }*/

    copy(new_coll,new_coll+4,act_coll);
    obtained = true;

}
void player::set_controller (Handler *controller){
    this->controller = controller;
}
void player::lose_life (){
    if (timeout == 0){
        this->controller->loss_energy (2);
        timeout = 400;
    }
}
