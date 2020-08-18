#include "transformations.h"
#include "includes.h"
#include "basic.h"
#include "generate.h"
#include "lincludes/mSDL_gfx.h"

namespace OGL{
    // El angulo 0 es normal y se va rotando hacia la izquierda 
    SDL_Surface* rotate_surface(SDL_Surface* src, double angle){
        return rotozoomSurface(src, angle, 1, 1);
    }
    // El zoom es el multiplicador por el cual se va a resizar el surface
    SDL_Surface* rotozoom_surface(SDL_Surface* src, double angle, double zoom){
        return rotozoomSurface(src, angle, zoom, 1);
    }
    // Los 2 zooms son los multiplicadores de tamanio de la X y la Y
    SDL_Surface* zoom_surface(SDL_Surface* src, double zoomX, double zoomY){
        return zoomSurface(src, zoomX, zoomY, 1);
    }
    void add_border(SDL_Surface* input,SDL_Color color){
        Uint32 pixel = SDL_MapRGB(input->format,color.r,color.g,color.b);
        for (int x = 0;x < input->w;x++){
            OGL::set_pixel(input,x,0         ,pixel);
            OGL::set_pixel(input,x,input->h-1,pixel);
        }
        for (int y = 0;y < input->h;y++){
            OGL::set_pixel(input,0,y         ,pixel);
            OGL::set_pixel(input,input->w-1,y,pixel);
        }
    }
    void border_surface(SDL_Surface* surface,int radius, bool Eiz_ar, bool Ede_ar, bool Eiz_ab, bool Ede_ab){
        /*
         if (Ede_ar){
         draw_arc(surface,radius,radius,radius,0,90,1000,LEFTCORR);
         }
         */
        int w = surface->w;
        int h = surface->h;
        w--;
        h--;
        SDL_Color transparent = OGL::c(0,0,1);
        Uint32 pixel = SDL_MapRGB(screen->format,transparent.r,transparent.g,transparent.b);
        
        double error = (double)-radius;
        double x = (double)radius;
        double y = 0;
        int cx = radius; int cy = radius;
        int mid_space_x = w-2*radius, mid_space_y = h-2*radius;
        while (y != radius+1){
            for (int v = cx - x;v >= 0;v--){
                if (Eiz_ab){
                    OGL::set_pixel(surface, (int)(v), (int)(cy + mid_space_y + y), pixel);
                }
                if (Eiz_ar) {
                    OGL::set_pixel(surface, (int)(v), (int)(cy - y), pixel);
                }
            }
            for (int v = cx + mid_space_x + x;v <= w;v++){
                if (Ede_ab){
                    OGL::set_pixel(surface, (int)(v), (int)(cy + mid_space_y + y), pixel);
                }
                if (Ede_ar){
                    OGL::set_pixel(surface, (int)(v), (int)(cy - y), pixel);
                }
            }
            for (int v = cy - x;v >= 0;v--){
                if (Ede_ar){
                    OGL::set_pixel(surface, (int)(cx + mid_space_x + y), (int)(v), pixel);
                }
                if (Eiz_ar) {
                    OGL::set_pixel(surface, (int)(cx - y), (int)(v), pixel);
                }
            }
            for (int v = cy + mid_space_y + x;v <= h;v++){
                if (Ede_ab){
                    OGL::set_pixel(surface, (int)(cx + mid_space_x + y), (int)(v), pixel);
                    
                }
                if (Eiz_ab) {
                    OGL::set_pixel(surface, (int)(cx - y), (int)(v), pixel);
                }
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
        SDL_SetColorKey( surface, SDL_TRUE, pixel );
        
    }
    SDL_Surface* flip_width_surface(SDL_Surface* surface){
        SDL_Surface* nueva = OGL::create_filled_surface (surface->w,surface->h,OGL::c(255,255,255));
        for (int y = 0;y < surface->h;y++){
            for (int x = 0;x < surface->w;x++){
                int xv = surface->w - x;
                int yv = y;
                Uint32 pixel = ((Uint32*)surface->pixels)[ y * surface->w + x ];
                OGL::set_pixel(nueva,xv,yv,pixel);
            }
        }
        *surface = *nueva;
        return nueva;
    }
    SDL_Surface* rotate_90(SDL_Surface* surface){
        SDL_Surface* nueva = OGL::create_filled_surface (surface->h,surface->w,OGL::c(255,255,255));
        for (int y = 0;y < surface->h;y++){
            for (int x = 0;x < surface->w;x++){
                Uint32 pixel = ((Uint32*)surface->pixels)[ y * surface->w + x ];
                OGL::set_pixel ( nueva , y , x , pixel);
            }
        }
        return nueva;
    }
}
