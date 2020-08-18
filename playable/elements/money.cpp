#include "money.h"
#include "images.h"

Money::Money(double value,double x,double y) : Element(){

    this->set_x (40);
    this->set_y (40);
    this->original_y = y;
    this->set_x (x);
    this->value = value;

    sy = 0;
    st = 0;

    if (value < 1.0){
        this->set_image ( images::money::cent.img );
    }else if(value < 10.0){
        this->set_image ( images::money::unit.img );
    }else if(value < 200.0){
        this->set_image ( images::money::units.img );
    }else if(value < 1500.0){
        this->set_image ( images::money::units7.img);
    }else if(value < 7500.0){ //7,5k
        this->set_image ( images::money::units9.img );
    }else if(value < 45000.0){ //45k
        this->set_image ( images::money::malet.img );
    }else if(value < 650000.0){ //650k
        this->set_image ( images::money::malet3.img);
    }else if(value < 1000000.0){ //1m
        this->set_image ( images::money::malet4.img);
    }else if(value < 50000000.0){ //50m
        this->set_image ( images::money::check.img );
    }else{
        this->set_image ( images::money::check2.img );
    }

    this->type = CASH;
}
void Money::update(){
    if (st){
        sy++;
        if (sy > 40){
            st = 0;
        }
    }else{
       sy--;
       if (sy <= 0){
            st = 1;
       }
    }
    this->set_y ( original_y + sy );

}
double Money::get_value (){
    return this->value;
}

