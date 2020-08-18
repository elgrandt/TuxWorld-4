#include <csignal>
#include <iostream>
#include "check_point.h"
#include "images.h"

using namespace std;

void add_image( Image img , vector <image_position_dimension> *cont ){
    cont->push_back( image_position_dimension( img.img , 0 , 0 , img.surface->w , img.surface->h ));
}

check_point::check_point() : ElementWIMG(){
    loops = 0;
    img   = 0;
    this->set_w(75);
    this->set_h(75);
    this->disabledraw ();
    this->set_type(MULTI_IMAGES);
    this->ticked = false;
    this->end_cycle = false;
    this->speed = 7;

    aumento = true;
}
void check_point::update (){
    if (this->ticked){
        this->loops ++;

    }
}
void check_point::tick(){
    if (not this->ticked){
        //something for checkpoint with stage

        add_image ( images::check_point_text["c"] , &this->myimages );
        add_image ( images::check_point_text["h"] , &this->myimages );
        add_image ( images::check_point_text["e"] , &this->myimages );
        add_image ( images::check_point_text["c"] , &this->myimages );
        add_image ( images::check_point_text["k"] , &this->myimages );

        add_image ( images::check_point_text["p"] , &this->myimages );
        add_image ( images::check_point_text["o"] , &this->myimages );
        add_image ( images::check_point_text["i"] , &this->myimages );
        add_image ( images::check_point_text["n"] , &this->myimages );
        add_image ( images::check_point_text["t"] , &this->myimages );
    }
    this->ticked = true;
}
void check_point::set_speed (int speed){
    this->speed = speed;
}
