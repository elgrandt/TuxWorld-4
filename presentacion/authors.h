#ifndef AUTHORS_H_
#define AUTHORS_H_
#include <iostream>
#include <vector>
#include <string>
#include "lincludes/mSDL_ttf.h"
#include "OGL/OGL.h"
#include "images.h"
using namespace std;

struct Text{
    GLint text; GLint text_first;
    int x; int y;
    int w; int h;
    SDL_Surface* surface; SDL_Surface* surface_first;
    string text_string;
    bool moving_out;
    int angle;
    int from_line;
};

class Authors{
    private:
        Image final_text;
        Image final_text_first;
        int angle;
        int speed;
        bool finished;
        int loops;
    public:
        int globalx;
        int globaly;
        vector<Text> texts;
        SDL_Color color_first;
        SDL_Color color_second;
        Authors();
        void set_text(vector<string> text);
        void update();
        bool get_finished();
};

#endif
