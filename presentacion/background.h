#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "OGL/OGL.h"

class Point{
    private:
        int x; int y;
        int angle;
        int speed;
        int STOPPER;
        int LOOPS;
    public:
        Point(int X, int Y, int ANGLE, int SPEED);
        void update();
        int get_x();
        int get_y();
};

class Background{
    private:
        OGL::color_change background;
        vector<Point> points;
        int LOOPS;
    public:
        Background();
        void update();
};

#endif
