#ifndef CHECK_POINT_H
#define CHECK_POINT_H

#include "element.h"

class check_point : public ElementWIMG{
    private:
        int loops;
        int img;
        bool aumento;
        bool ticked;
        bool end_cycle;
        int speed;
    public:
        check_point();
        void update ();
        void tick();
        void set_speed(int speed);
};

#endif // CHECK_POINT_H
