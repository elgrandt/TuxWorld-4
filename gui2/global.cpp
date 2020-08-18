#include "global.h"
#include <iostream>
using namespace std;

namespace shared {

    /*** POSITION AND DIMENSION ***/

    bool square::focused(int mx, int my){
        if (mx > this->x and mx < this->x + this->w){
            if (my > this->y and my < this->y + this->h){
                return true;
            }
        }
        return false;
    }

    /*** call functions ***/
    void events_call_functions::kill(){
        this->up_container->remove_element(this);
    }
    void events_call_functions::set_container(shared::call_element_container* container){
        this->up_container = container;
    }
    void events_call_functions::set_event_status_data(shared::data_events* events){
        this->events_status = events;
    }

    /*** call element ***/
    void call_element::call_mouse_motion(int x,int y){
        this->handle_mouse_motion(x,y);
    }
    void call_element::call_mouse_down(){
        this->handle_mouse_down();
    }
    void call_element::call_mouse_up(){
        this->handle_mouse_up();
    }
    void call_element::call_update(){
        this->handle_update();
    }
    void call_element::call_draw(){
        this->handle_draw();
    }

    /*** call element container ***/
    void call_element_container::call_mouse_motion(int x, int y){
        this->handle_mouse_motion(x,y);
        for (int index = 0;index < this->into_elements.size();index++){
            this->into_elements[index]->call_mouse_motion(x,y);
        }
    }
    void call_element_container::call_mouse_down(){
        this->handle_mouse_down();
        for (int index = 0;index < this->into_elements.size();index++){
            this->into_elements[index]->call_mouse_down();
        }
    }
    void call_element_container::call_mouse_up(){
        this->handle_mouse_up();
        for (int index = 0;index < this->into_elements.size();index++){
            this->into_elements[index]->call_mouse_up();
        }
    }
    void call_element_container::add_element(shared::events_call_functions* element){
        element->set_container(this);
        element->set_event_status_data(this->events_status);
        this->into_elements.push_back(element);
    }
    void call_element_container::remove_element(shared::events_call_functions* element){
        for (int index = 0;index < this->into_elements.size();index++){
            if (this->into_elements[index] == element){
                this->into_elements.erase(this->into_elements.begin() + index );
                delete element;
            }
        }
    }
    void call_element_container::call_draw(){
        for (int index = 0;index < this->into_elements.size();index++){
            this->into_elements[index]->call_draw();
        }
        this->handle_draw();
    }
    void call_element_container::call_update(){
        for (int index = 0;index < this->into_elements.size();index++){
            this->into_elements[index]->call_update();
        }
        this->handle_update();
    }
    vector <events_call_functions*>* call_element_container::get_into(){
        return &this->into_elements;
    }
}
