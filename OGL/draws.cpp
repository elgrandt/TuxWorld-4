#include "draws.h"
#include "includes.h"
#include "basic.h"

namespace OGL{
    void draw_circle(SDL_Surface* surface,SDL_Color color,double cx,double cy,int radius){
        if (surface != NULL){
            double error = (double)-radius;
            double x = (double)radius;
            double y = 0;
            Uint32 pixel = SDL_MapRGB(surface->format,color.r,color.g,color.b);

            while (x >= y){
                OGL::set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
                OGL::set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

                if (x != 0){
                    OGL::set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
                    OGL::set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
                }

                if (y != 0){
                    OGL::set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
                    OGL::set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
                }

                if (x != 0 && y != 0){
                    OGL::set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
                    OGL::set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
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
    }
    void line( SDL_Surface* surface,float x1, float y1, float x2, float y2, Uint32 pixel){
        // Bresenham's line algorithm
        const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
        if(steep){
            std::swap(x1, y1);
            std::swap(x2, y2);
        }

        if(x1 > x2){
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const float dx = x2 - x1;
        const float dy = fabs(y2 - y1);

        float error = dx / 2.0f;
        const int ystep = (y1 < y2) ? 1 : -1;
        int y = (int)y1;

        const int maxX = (int)x2;

        for(int x=(int)x1; x<maxX; x++){
            if(steep){
                OGL::set_pixel(surface,y,x, pixel);
            }
            else{
                OGL::set_pixel(surface,x,y, pixel);
            }

            error -= dy;
            if(error < 0)
            {
                y += ystep;
                error += dx;
            }
        }
    }
    void draw_arc(SDL_Surface* surface,double cx, double cy, float r, double start_angle, double arc_angle, int num_segments,int special){
        start_angle *= GL_PI / 180.0;
        arc_angle   *= GL_PI / 180.0;

        SDL_Color transparent = c(0,0,1);
        Uint32 pixel = SDL_MapRGB(screen->format,transparent.r,transparent.g,transparent.b);

        double theta = arc_angle / double(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        double tangetial_factor = tanf(theta);
        double radial_factor = cosf(theta);

        double x = r * cosf(start_angle);//we now start at the start angle
        double y = r * sinf(start_angle);

        int lx; int ly; bool mystart = false;
        for(int ii = 0; ii < num_segments; ii++){
            //cout<<x+cx<<" "<<y+cy<<endl;
            /*if (mystart){
             line(surface,lx,ly,cx+x,cy+y,pixel);
             }else{
             mystart = true;
             }
             lx = cx + x;
             ly = cy + y;*/
            int dx;
            int dy;
            bool normal = false;
            switch (special){
                case LEFTCORR:
                    for (int vx = cx + x;vx >= 0;vx--){
                        OGL::set_pixel(surface, (int)vx, (int)(y + cy), pixel);
                    }
                    break;
                case RIGHTCORR:
                    for (int vx = cx-1;vx > x + cx-1;vx--){
                        OGL::set_pixel(surface, (int)vx, (int)(y + cy), pixel);
                    }
                    break;
                case UPCORR:
                    for (int vy = cy;vy < cy+y;vy++){
                        OGL::set_pixel(surface, (int)(x + cx), (int)(vy), pixel);
                    }
                    break;
                case DOWNCORR:
                    for (int vy = cy-1;vy > cy+y-1;vy--){
                        OGL::set_pixel(surface, (int)(x + cx), (int)(vy), pixel);
                    }
                    break;
                case NOSPECIAL:
                    OGL::set_pixel(surface, (int)(x + cx), (int)(y + cy), pixel);
                    break;
            }

            double tx = -y;
            double ty = x;
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;

            x *= radial_factor;
            y *= radial_factor;
        }
        SDL_SetColorKey( surface, SDL_TRUE, pixel );
    }
}
