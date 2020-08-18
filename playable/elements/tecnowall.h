#ifndef TECNOWALL_H
#define TECNOWALL_H

#include "element.h"
#include "wall.h"
#include <iostream>
#include <vector>
#include "OGL/OGL.h"
#include "lincludes/mSDL.h"
#include "images.h"
using namespace std;

#define FIRST -1
#define MAX_WALLS 1000

struct AdvancedWall{
    int x; int y; int cx; int cy; Image img; int ver_hor;
};

struct AdvancedCorner{
    int x; int y; int angle; int size; GLuint img;
};

class Tecnowall : public Element{
    public:
        int act_wall; int act_corner;
        int walls_size[2];
        AdvancedWall walls[MAX_WALLS];
        AdvancedCorner corners[MAX_WALLS];
        Tecnowall();
        void update();
        void update_graphics();
        int add_first_wall(int cx, int cy, bool ver_hor, int x, int y);
        int add_wall(int cx, int cy, int izq_der, int position, int reference);
        void add_corner(int reference, int arr_aba, int izq_der);
        Image get_image(bool ver_hor);
        void change_walls_size(int new_w, int new_h);
};

#endif // TECNOWALL_H
