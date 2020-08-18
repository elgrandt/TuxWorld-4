#ifndef WALL_H
#define WALL_H

#include "element.h"
#include "images.h";

#define HORIZONTAL 0
#define VERTICAL   1
#define IZQUIERDA  2
#define DERECHA    3
#define ARRIBA     4
#define ABAJO      5

class wall : public Element{
    public:
        wall(int rx,int ry,Image image,bool hv);
        void update();
};

wall* classic_wall_horizontal(int w,int h);
wall* classic_wall_vertical  (int w,int h);
#endif // WALL_H
