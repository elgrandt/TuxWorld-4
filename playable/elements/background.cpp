#include "background.h"
#include "images.h"
#include "OGL/blits.h"

background::background(GLuint image,int ax,int ay,int w,int h,int x,int y) : Element(){
    this->set_image ( image );
    this->set_type ( BACKGROUND );

    this->set_x (x);
    this->set_y (y);
    this->set_w (w);
    this->set_h (h);
    this->set_rx(ax);
    this->set_ry(ay) ;
}

void background::update (){

}

background* get_classic_background(int ax,int ay,int w,int h,int x,int y){
    background* nuevo = new background(images::background::classic.img,ax,ay,w,h,x,y);
    return nuevo;
}

