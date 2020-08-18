#include <sstream>

#include "handler.h"
#include "OGL/blits.h"
#include "images.h"

string itss(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}
string dtss(double n){
    stringstream ss;
    ss << n;
    return ss.str();
}

GLuint text_surface(string text){
    return OGL::generate_texture( TTF_RenderText_Blended(fonts::calibri_c,text.c_str(),OGL::c(0,0,0) ) );
}

Handler::Handler(){
    go_up = false;
    go_down = false;
    go_left = false;
    go_right = false;

    lives    = 5;
    energy   = 10;
    money    = 0.0;
    this->set_name("Tux Kernel");
}
void Handler::set_player (player *play){
    this->central = play;
}
void Handler::keydown (int key){
    switch (key){
        case SDLK_RIGHT:
            go_right = true;
        break;
        case SDLK_LEFT:
            go_left = true;
        break;
        case SDLK_UP:
            go_up = true;
        break;
        case SDLK_DOWN:
            go_down = true;
        break;
    }
}
void Handler::keyup(int key){
    switch (key){
        case SDLK_RIGHT:
            go_right = false;
        break;
        case SDLK_LEFT:
            go_left = false;
        break;
        case SDLK_UP:
            go_up = false;
        break;
        case SDLK_DOWN:
            go_down = false;
        break;
    }
}
void Handler::take_action(){

    if (go_up  ) {  this->central->move_up    (); }
    if (go_down) {  this->central->move_down  (); }
    if (go_left) {  this->central->move_left  (); }
    if (go_right){  this->central->move_right (); }
}
void Handler::set_name(string name){
    glDeleteTextures(1,&this->surface_name);
    this->surface_name = text_surface(name);
}
void Handler::add_live(){
    this->lives ++;
}
void Handler::kill_live(){
    if (this->lives >= 0){
        this->lives --;
        this->update_lives_surface();
    }else{
        this->central->kill();
    }
}
int Handler::get_energy (){
    return this->energy;
}
void Handler::loss_energy (int amount){
    this->energy -= amount;
    if (this->energy == 0){
        this->kill_live ();
    }
}

void Handler::give_money(double amount){
    this->money += amount;
    this->update_money_surface();
}
void Handler::update_money_surface(){
    if (money < 1.0){
        int cents = money * 100;
        this->surface_money = text_surface(itss(cents)+" c");
    }else if(money < 1000){
        int units = money;
        int decimal = ( money - int(money) ) * 10;
        this->surface_money = text_surface(itss(units)+"."+itss(decimal)+" $");
    }else if(money < 1000*1000){
        int kilos = money / 1000;
        int decimal = (money/1000 - int(money/1000) ) * 10;
        this->surface_money = text_surface(itss(kilos)+"."+itss(decimal)+" k");
    }else if (money < 1000*1000*1000){
        int megas = money / 1000000;
        int decimal = (money/1000000 - int(money/1000000) ) * 10;
        this->surface_money = text_surface(itss(megas)+"."+itss(decimal)+" M");
    }else{
        int mm = money / 100000000000;
        int decimal = (money/1000000000 - int(money/1000000000) ) * 10;
        this->surface_money = text_surface(itss(mm)+"."+itss(decimal)+" MM");
    }
}
void Handler::update_lives_surface(){
    this->surface_lives = text_surface(itss(this->lives));
}

GLuint Handler::get_surface_money(){
    return this->surface_money;
}

GLuint Handler::get_surface_name(){
    return this->surface_name;
}

player* Handler::get_central (){
    return this->central;
}
