#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "lincludes/mSDL.h"
#include "element.h"
#include "images.h"

class background : public Element{
    private:
        double ax;
        double ay;
    public:
        background(GLuint image,int ax,int ay,int w,int h,int x,int y);
        void update();
        double get_ax();
        double get_ay();
};

background* get_classic_background(int ax,int ay,int w,int h,int x,int y);

#endif // BACKGROUND_H
