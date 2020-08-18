#include "element.h"
#include "images.h"
#include "../stage.h"

Element::Element(){
    this->set_x(0);
    this->set_y(0);
    this->set_w(40);
    this->set_h(40 );
    this->tags[ TAG_PLAYER ] = false;
    this->tags[ TAG_WALL   ] = false;
    this->tags[ TECNOWALL ] = false;
    this->type = ELEMENT;

    this->set_rx (1);
    this->set_ry (1);
    draw_enable = true;
}
void Element::initializate (Stage *my_stage){
    this->outside = my_stage;
}
double  Element::get_x(      ){ return x;                      }
double  Element::get_y(      ){ return y;                      }
void Element::set_x(double x ){ this->x = x;                   }
void Element::set_y(double y ){ this->y = y;                   }
void Element::sum_x(double sx){ this->set_x(this->get_x()+sx); }
void Element::sum_y(double sy){ this->set_y(this->get_y()+sy); }
int  Element::get_w(      ){ return this->W;                }
int  Element::get_h(      ){ return this->H;                }
void Element::set_w(int w ){ this->W = w;                   }
void Element::set_h(int h ){ this->H = h;                   }
bool Element::is_on(      ){ return this->on;               }
GLuint Element::get_image(  ){ return this->image;            }
void Element::set_image(GLuint image){
    this->image = image;
}
void Element::add_tag (int tag){
    this->tags[tag] = true;
}
void Element::set_type (int TYPE){
    this->type = TYPE;
}
int Element::get_type (){
    return this->type;
}
void Element::set_position (double x, double y){
    this->set_x (x);
    this->set_y (y);
}
bool Element::is_tag (int tag){
    return this->tags[tag];
}
int Element::get_rx (){
    return this->rx;
}
int Element::get_ry (){
    return this->ry;
}
void Element::set_rx(int rx){
    this->rx = rx;
}
void Element::set_ry (int ry){
    this->ry = ry;
}
void Element::kill(){
    for (int x = 0;x < outside->container.size();x++){
        if (outside->container[x] == this){
            outside->container.erase(outside->container.begin() + x);
        }
    }
    for (int x = 0;x < outside->types[this->type].size();x++){
        if (outside->types[this->type][x] == this){
            outside->types[this->type].erase(outside->types[this->type].begin() + x);
        }
    }
    delete this;
}
void Element::enabledraw (){
    this->draw_enable = true;
}
void Element::disabledraw (){
    this->draw_enable = false;
}
bool Element::checkdraw (){
    return this->draw_enable;
}

Root::Root() : Element(){
    this->set_image( images::tux[0].img );
    this->set_type ( ELEMENT );
}
void Root::update(){

}
Root::~Root(){

}
vector <image_position_dimension> ElementWIMG::get_images(){
    return this->myimages;
}
image_position_dimension::image_position_dimension(GLuint Dimage, double Dx,double Dy,int Dw, int Dh){
    image = Dimage;
    x     = Dx;
    y     = Dy;
    w     = Dw;
    h     = Dh;
}
