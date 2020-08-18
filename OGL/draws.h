#ifndef DRAWS_H_
#define DRAWS_H_
#include "includes.h"

namespace OGL{
    void draw_circle(SDL_Surface* surface,SDL_Color color,double cx,double cy,int radius);
    void line( SDL_Surface* surface,float x1, float y1, float x2, float y2, Uint32 pixel);
    void draw_arc(SDL_Surface* surface,double cx, double cy, float r, double start_angle, double arc_angle, int num_segments,int special);

    struct color_change{
        double r;
        double g;
        double b;
        int state;
        double scale;
        int max_color;
        int min_color;
        color_change(){
            r = 0;
            g = 0;
            b = 0;
            state = 0;
            max_color = 255;
            min_color = 0;
        }
        void update(){
            if (state == 0){
                r += scale;
                if (r >= max_color){
                    state = 1;
                }
            }else if(state == 1){
                g += scale;
                if (g >= max_color){
                    state = 2;
                }
            }else if (state == 2){
                r -= scale;
                b += scale;
                if (b >= max_color or g <= min_color){
                    state = 3;
                }
            }else if(state == 3){
                g -= scale;
                b -= scale;
                if (g <= min_color or b <= min_color){
                    state = 0;
                }
            }
        }
    };
}

#endif
