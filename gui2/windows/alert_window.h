/*
 * File:   alert_window.h
 * Author: ariel
 *
 * Created on June 21, 2014, 12:00 PM
 */

#ifndef ALERT_WINDOW_H
#define	ALERT_WINDOW_H


#include "gui2/global.h"

class alert_window : shared::call_element{
    public:
        alert_window(int px,int py);

    private:
        void handle_update();
        void handle_draw();
};

#endif	/* ALERT_WINDOW_H */

