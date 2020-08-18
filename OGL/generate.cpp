#include "generate.h"
#include "includes.h"
#include "basic.h"
#include "draws.h"

namespace OGL{
    SDL_Surface* create_void_surface(int width,int height){
        Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif
        SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32,rmask, gmask, bmask, amask);
        return surface;
    }
    SDL_Surface* create_filled_surface(int width,int height,SDL_Color color){
        SDL_Surface* surface = OGL::create_void_surface(width,height);
        SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = width; rect.h = height;
        SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,color.r,color.g,color.b));
        return surface;
    }
    SDL_Surface* create_circle(SDL_Color color,int radius){
        SDL_Surface *surface;
        int width = radius*2;
        int height = radius*2;
        surface = OGL::create_void_surface(width,height);
        OGL::draw_circle(surface,OGL::c(255,0,0),radius,radius,radius);
        return surface;
    }
    SDL_Surface* create_filled_circle(SDL_Color color,int radius){
        SDL_Surface *surface = OGL::create_void_surface(radius*2,radius*2);
        int cx = radius; int cy = radius;
        if (surface != NULL){
            double error = (double)-radius;
            double x = (double)radius;
            double y = 0;
            Uint32 pixel = SDL_MapRGB(surface->format,color.r,color.g,color.b);

            while (x >= y){
                for (int v = cx - x;v <= cx + x;v++){
                    OGL::set_pixel(surface, (int)(v), (int)(cy + y), pixel);
                    OGL::set_pixel(surface, (int)(v), (int)(cy - y), pixel);
                }
                for (int v = cy - x;v <= cy + x;v++){
                    OGL::set_pixel(surface, (int)(cx + y), (int)(v), pixel);
                    OGL::set_pixel(surface, (int)(cx - y), (int)(v), pixel);
                }

                error += y;
                y++;
                error += y;

                if (error >= 0){
                    x--;
                    error -= x;
                    error -= x;
                }
            }
        }else{
            cout<<"Surface is null"<<endl;
        }
        return surface;
    }
}
