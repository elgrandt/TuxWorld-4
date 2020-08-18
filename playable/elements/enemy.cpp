#include <math.h>
#include <iostream>

#include "enemy.h"
#include "images.h"
#include "utilities.h"
#include "playable/collision.h"
#include "playable/elements/tecnowall.h"

#define GL_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

using namespace std;

enemy::enemy(double X,double Y) : Element(){
    angle       = 10.0;
    speed       = 6;
    this->set_type ( ENEMY );
    this->set_x (X);
    this->set_y (Y);
    destroy     = false;
    char image  = 0;
    char time   = 0;
    this->set_w(50);
    this->set_h(50);
}
void enemy::update (){
    check_collision ();
    this->sum_x ( sin (angle) * this->speed );
    this->sum_y ( cos (angle) * this->speed );

    enemy_update ();
    if (destroy){
        destroy_sequence();
    }
}
void enemy::check_collision (){
    for (int e = 0;e < outside->container.size ();e++){
        if (outside->container[e]->tags[TAG_WALL] || outside->container[e]->tags[TAG_PLAYER]){
            collist sum = get_max_collide(this, outside->container[e] );
            for (int f = 0;f < sum.size ();f++){
                handle_collision ( sum[f] ,outside->container[e]);
            }
        }
    }
    for (int e = 0;e < outside->types[TECNOWALL].size();e++){
        Tecnowall* tt = (Tecnowall*)outside->types[TECNOWALL][e];
        for (int w = 0;w < tt->act_wall;w++){
            Root t = Root();
            t.set_x ( tt->walls[w].x );
            t.set_y ( tt->walls[w].y );
            t.set_w ( tt->walls[w].cx * tt->walls[w].img.w );
            t.set_h ( tt->walls[w].cy * tt->walls[w].img.h );
            collist sum = get_max_collide(this , &t);
            for (int f = 0;f < sum.size();f++){
                handle_collision ( sum[f] ,tt);
            }
        }
    }
}
void enemy::handle_collision (collision c,epointer e){
    enemy_collision (c,e);
}
double enemy::get_angle (){
    return this->angle;
}
void enemy::set_angle (double angle){
    this->angle = angle;
}
void enemy::destroy_sequence(){

}
void enemy::destroyme(){
    destroy = true;
}

classic_enemy::classic_enemy(double x,double y) : enemy(x,y){
    set_image ( images::enemies::classical[0].img );
    timer  = 0;
    imager = 0;
}

void classic_enemy::enemy_update (){

}
void classic_enemy::enemy_collision (collision c,epointer e){
    if (e->is_tag(TAG_WALL)){
        if (c.side == coll::up){
            this->set_angle ( GL_PI - this->get_angle () );
        }else if(c.side == coll::left){
            this->set_angle ( this->get_angle () + (GL_PI - this->get_angle ()) * 2 );
        }else if(c.side == coll::down){
            this->set_angle ( GL_PI - this->get_angle () );
        }else if(c.side == coll::right){
            this->set_angle ( this->get_angle () + (GL_PI - this->get_angle ()) * 2 );
        }
    }else if(e->is_tag(TAG_PLAYER)){
        this->destroyme();
        player* p = (player*)e;
        p->lose_life ();
    }
}
void classic_enemy::destroy_sequence(){
    timer ++;
    if (timer > 2){
        imager ++;
        timer = 0;
        this->set_image( images::enemies::classical[imager].img );
        if (imager == images::enemies::classical.size() - 1){
            this->kill();
        }
    }
}

sequencial_enemy::sequencial_enemy(double x,double y, vector <pair<int,int> > areas) : enemy(x,y){
    iamnow = 0;
    go_list = areas;
}
void sequencial_enemy::enemy_update (){
    pair <int,int> actual = go_list[iamnow];
    int tx = actual.first;
    int ty = actual.second;

    int dx = abs (tx - this->get_x () );
    int dy = abs( ty - this->get_y () );

    int angulo;

    if (dx > 0 && dy > 0){ //cuadrante 1

    }else if(dx > 0 && dy < 0){ //cuadrante 2

    }else if(dx < 0 && dy < 0){ //cuadrante 3

    }else if(dx < 0 && dy > 0){ //cuadrante 4

    }

    //this->set_angle();

}

void sequencial_enemy::enemy_collision (collision c,epointer e){
    
}

void sequencial_enemy::destroy_sequence(){
    
}
