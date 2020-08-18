/*
 * File:   alert_window.cpp
 * Author: ariel
 *
 * Created on June 21, 2014, 12:00 PM
 */

#include "alert_window.h"
#include "gui2/globaL.h"
#include <iostream>
using namespace std;

alert_window::alert_window(int px,int py){
    cout<<"HOLA1"<<endl;
}

void alert_window::handle_update(){
    cout<<"HOLA2"<<endl;
}

void alert_window::handle_draw(){
    cout<<"HOLA3"<<endl;
}
