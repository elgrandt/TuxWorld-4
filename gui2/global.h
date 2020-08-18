/*
 * File:   global.h
 * Author: ariel
 *
 * Created on June 20, 2014, 4:00 PM
 */

#ifndef GLOBAL_H_
#define	GLOBAL_H_

#include <vector>

using namespace std;

namespace shared{
    /*** Pre-prototipes ***/
    struct position;
    struct dimension;
    struct data_events;

    class events_call_functions;
    class call_element;
    class call_element_container;

    struct data_events{
        int mouse_x;
        int mouse_y;
    };
    class position{
        public:
            int x;
            int y;
    };
    class dimension{
        public:
            int w;
            int h;
    };
    class square : public position , public dimension{
        bool focused(int mx,int my);
    };
    class events_call_functions {
        protected:

            // my top container
            call_element_container* up_container;

            // data events pointer
            data_events* events_status;

            /*** HANDLING PARTICULAR EVENTS ***/
            virtual void handle_mouse_motion(int x,int y) = 0;
            virtual void handle_mouse_down() = 0;
            virtual void handle_mouse_up() = 0;
            virtual void handle_update() = 0;

            /*** MY GRAPHIC UPDATE ***/
            virtual void handle_draw() = 0;

        public:
            /*** EVENTS OUT CALL ***/
            virtual void call_mouse_motion(int x,int y) = 0;
            virtual void call_mouse_down() = 0;
            virtual void call_mouse_up() = 0;

            /*** TIMER OUT CALL ***/
            virtual void call_update() = 0;

            /*** MY GRAPHIC OUT CALL ***/
            virtual void call_draw() = 0;

            /*** TOP handling ***/
            void kill();
            void set_container(call_element_container* container);
            void set_event_status_data(data_events* events);

    };

    class call_element : public events_call_functions{
        public:
            /*** WRITE OUT CALLS ***/
            void call_mouse_motion(int x,int y);
            void call_mouse_down();
            void call_mouse_up();

            /*** WRITE TIMER CALL ***/
            void call_update();

            /*** WRITE GRAPHIC CALL ***/
            void call_draw();

    };

    class call_element_container : public events_call_functions{
        protected:
            vector <events_call_functions*> into_elements;


        public:
            /*** MY EXTRA FUNCTIONS ***/
            void add_element(events_call_functions* element);
            void remove_element(events_call_functions* element);


            /*** WRITE OUT CALLS ***/
            void call_mouse_motion(int x,int y);
            void call_mouse_down();
            void call_mouse_up();

            /*** WRITE TIMER CALL ***/
            void call_update();

            /*** WRITE GRAPHIC CALL ***/
            void call_draw();
            vector <events_call_functions*>* get_into();
    };

}

#endif	/* GLOBAL_H */

