#ifndef STAGE_H_
#define STAGE_H_

#include <iostream>
#include <vector>

#include "utilities.h"
#include "handler.h"
#include "elements/element.h"
#include "collision.h"

using namespace std;

typedef Element* epointer;
typedef vector <epointer>* pcontainer;


class Stage{
    private:
        int focus;
        double check_point_x; double check_point_y;
    public:
        vector <epointer> container;
        vector <epointer> types[AMOUNT_TYPES];

        vector <Handler*> level_players;
        int speed_update;

        Stage();

        void add_player(int position_x,int position_y,Handler* controller);
        void add_element(epointer adding);
        void remove_element(Element* remove);
        void check_delete();
        void update();

        void save_check_point(double xpoint,double ypoint);
};

class graphic_stage : public Stage{
    private:
        int focus;

        double zoom;
        int camera_x;
        int camera_y;
        bool parcial;

    public:
        graphic_stage();
        void draw();
        void draw_layer(int layer);
        void set_focus_player(int ID);
        void update_camera();

        void set_zoom(double factor);
        void set_natural_zoom();
        void sum_zoom(double value);
        void update_screener();
};

#endif
