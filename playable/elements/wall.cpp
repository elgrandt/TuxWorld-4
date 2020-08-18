#include "wall.h"
#include "playable/stage.h"
#include "OGL/blits.h"
#include "images.h"

wall::wall(int rx,int ry,Image image,bool hv) : Element(){
    add_tag ( TAG_WALL );
    set_type (WALL);
    
    int w = image.w, h = image.h;
    this->set_image ( image.img );
    w = w*rx;
    h = h*ry;
    this->set_w (w);
    this->set_h (h);
    this->set_rx(rx);
    this->set_ry(ry);
}
void wall::update (){

}
wall* classic_wall_horizontal(int ax,int ay){
    return new wall( ax , ay , images::wall::normal,HORIZONTAL);
}
wall* classic_wall_vertical  (int ax,int ay){
    return new wall( ax , ay , images::wall::d90,VERTICAL);
}
