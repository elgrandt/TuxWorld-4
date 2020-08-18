#include "tecnowall.h"

#include <iostream>
#include "lincludes/mSDL.h"
#include "lincludes/mSDL_gfx.h"
#include "OGL/OGL.h"
#include "wall.h"
#include "images.h"
using namespace std;

Tecnowall::Tecnowall() : Element(){
    this->set_type(TECNOWALL);
    this->add_tag(TECNOWALL);
    this->add_tag(TAG_WALL);
    this->act_corner = 0;
    walls_size[0] = images::wall::normal.w;
    walls_size[1] = images::wall::normal.h;
}

Image Tecnowall::get_image(bool ver_hor){
    Image img;
    if (ver_hor == HORIZONTAL) {
        img = images::wall::normal;
        img.w = walls_size[0];
        img.h = walls_size[1];
    }else{
        img = images::wall::d90;
        img.w = walls_size[1];
        img.h = walls_size[0];
    }
    return img;
}

int Tecnowall::add_first_wall(int cx, int cy, bool ver_hor, int x, int y){
    AdvancedWall add = AdvancedWall();
    add.cx = cx; add.cy = cy;
    add.x = x; add.y = y;
    add.ver_hor = ver_hor;
    add.img = get_image(ver_hor);
    walls[0] = add;
    act_wall = 1;
    return 0;
}

int Tecnowall::add_wall(int cx, int cy, int izq_der, int position, int reference){
    AdvancedWall ant = walls[reference];
    
    AdvancedWall add = AdvancedWall();
    add.cx = cx; add.cy = cy;
    add.ver_hor = not ant.ver_hor;
    add.img = get_image(add.ver_hor);
    
    int dif = 0;
    if (position == 0) {
        dif = get_image(HORIZONTAL).h;
    }else{
        dif = get_image(HORIZONTAL).h/2;
    }
    
    int wallW = add.img.w;
    int wallH = add.img.h;
    if (add.ver_hor == VERTICAL) {
        if (position >= ant.cx) {
            position = ant.cx;
            dif = 0;
        }
    }else{
        if (position >= ant.cy) {
            position = ant.cy;
            dif = 0;
        }
    }
    if (add.ver_hor == VERTICAL) {
        add.x = ant.x + position*wallH-dif;
        if (izq_der == IZQUIERDA) {
            add.y = ant.y + ant.img.h;
        }else{
            add.y = ant.y - cy*wallH;
        }
    }else{
        add.y = ant.y + position*wallW-dif;
        if (izq_der == IZQUIERDA) {
            add.x = ant.x - cx*wallW;
        }else{
            add.x = ant.x + ant.img.w;
        }
    }
    
    int add_corner = false;
    AdvancedCorner advc;
    if (position == 0) {
        if (add.ver_hor == VERTICAL) {
            advc.x = ant.x - get_image(HORIZONTAL).h;
            advc.y = ant.y;
            if (izq_der == IZQUIERDA) {
                advc.angle = 90;//|_
            }else{
                advc.angle = 0;//|-
            }
        }else{
            advc.x = ant.x;
            advc.y = add.y;
            if (izq_der == IZQUIERDA) {
                advc.angle = 180;//_|
            }else{
                advc.angle = 90;//|_
            }
        }
        add_corner = true;
    }else{
        bool cond = false;
        if (ant.ver_hor == HORIZONTAL) {
            if (position >= ant.cx) {
                cond = true;
            }
        }else{
            if (position >= ant.cy) {
                cond = true;
            }
        }
        if (cond) {
            if (add.ver_hor == VERTICAL) {
                advc.x = add.x;
                advc.y = ant.y;
                if (izq_der == IZQUIERDA) {
                    advc.angle = 180;//_|
                }else{
                    advc.angle = 270;//-|
                }
            }else if (add.ver_hor == HORIZONTAL){
                advc.x = ant.x;
                advc.y = add.y;
                if (izq_der == IZQUIERDA) {
                    advc.angle = 270;//-|
                }else{
                    advc.angle = 0;//|-
                }
            }
            add_corner = true;
        }
    }
    if (add.ver_hor == VERTICAL) {
        advc.size = add.img.w;
    }else{
        advc.size = add.img.h;
    }
    if (add_corner) {
        SDL_Surface* new_surf = OGL::rotate_surface(images::wall::esquina.surface, advc.angle);
        advc.img = OGL::generate_texture(new_surf);
        SDL_FreeSurface(new_surf);
        corners[act_corner] = advc;
        act_corner++;
    }
    
    walls[act_wall] = add;
    act_wall++;
    return act_wall-1;
}

void Tecnowall::add_corner(int reference, int arr_aba, int izq_der){
    AdvancedCorner add;
    AdvancedWall ref = walls[reference];
    
    if (ref.ver_hor == VERTICAL) {
        add.size = ref.img.w;
        add.x = ref.x;
        if (arr_aba == ARRIBA) {
            add.y = ref.y + ref.cy*ref.img.h;
            if (izq_der == IZQUIERDA) {
                add.angle = 270;//-|
            }else{
                add.angle = 0;//|-
            }
        }else{
            add.y = ref.y - add.size;
            if (izq_der == IZQUIERDA) {
                add.angle = 180;//_|
            }else{
                add.angle = 90;//|_
            }
        }
    }else{
        add.size = ref.img.h;
        add.y = ref.y;
        if (izq_der == IZQUIERDA) {
            add.x = ref.x - add.size;
            if (arr_aba == ARRIBA) {
                add.angle = 90;//|_
            }else{
                add.angle = 0;//|-
            }
        }else{
            add.x = ref.x + ref.cx*ref.img.w;
            if (arr_aba == ARRIBA) {
                add.angle = 180;//_|
            }else{
                add.angle = 270;//-|
            }
        }
    }
    
    SDL_Surface* new_surf = OGL::rotate_surface(images::wall::esquina.surface, add.angle);
    add.img = OGL::generate_texture(new_surf);
    SDL_FreeSurface(new_surf);
    corners[act_corner] = add;
    act_corner++;
}

void Tecnowall::update_graphics(){
    for (int x = 0; x < this->act_wall; x++) {
        AdvancedWall* ACTUAL = &this->walls[x];
        OGL::blit_texture( ACTUAL->img.img, ACTUAL->x, ACTUAL->y, ACTUAL->img.w*ACTUAL->cx, ACTUAL->img.h*ACTUAL->cy, ACTUAL->cx, ACTUAL->cy);
    }
    for (int x = 0; x < this->act_corner; x++) {
        OGL::blit_texture(this->corners[x].img, this->corners[x].x, this->corners[x].y, this->corners[x].size, this->corners[x].size);
    }
}

void Tecnowall::change_walls_size(int new_w, int new_h){
    this->walls_size[0] = new_w;
    this->walls_size[1] = new_h;
}

void Tecnowall::update(){
    
}
