#ifndef MENU_H_
#define MENU_H_
#include "lincludes/mSDL.h"
#include "lincludes/mOPENGL.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BotonMenu{
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
    GLint texture;
    string title;
    bool hover(int X,int Y);
    void update(int mX,int mY);
    void generate_texture();
};

class Menu{
    private:
        vector<BotonMenu> botones;
        SDL_MouseMotionEvent* mouse;
    public:
        void update();
        void start();
        void set_events(SDL_MouseMotionEvent* new_mouse);
};

#endif // MENU_H_
