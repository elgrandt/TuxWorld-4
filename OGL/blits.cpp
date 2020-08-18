#include "generate.h"
#include "blits.h"
#include "includes.h"
#include "lincludes/mSDL.h"
#include "lincludes/mOPENGL.h"
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
/*  BACKUP
 
 
 void blit_texture(GLuint texture,int x,int y,int w,int h,int rx,int ry){
 glBindTexture( GL_TEXTURE_2D, texture );
 glEnable( GL_TEXTURE_2D );
 
 glBegin(GL_QUADS);
 glLoadIdentity ();
 glTexCoord2f(   0,   0 );  glVertex2f(x    ,  y );
 glTexCoord2f(rx  ,   0 );  glVertex2f(x + w,  y );
 glTexCoord2f(rx  ,  -ry);  glVertex2f(x + w,  y + h);
 glTexCoord2f(0   ,  -ry);  glVertex2f(x    ,  y + h);
 glEnd();
 
 glDisable( GL_TEXTURE_2D );
 }
 
*/

namespace OGL{
    void dibujar_cuadrado(int ancho,int alto,int x,int y,SDL_Color color){
        glColor3ub(color.r,color.g,color.b);
        glBegin(GL_QUADS);
        glVertex3f( x         , y         , 0.0f);
        glVertex3f( x + ancho , y         , 0.0f);
        glVertex3f( x + ancho , y + alto  , 0.0f);
        glVertex3f( x         , y + alto  , 0.0f);
        glEnd();
    }
    GLuint generate_texture(SDL_Surface* surface){
        GLint format;
        if ( surface->format->BytesPerPixel == 3 ){
            format = GL_RGB;
        }else if ( surface->format->BytesPerPixel == 4 ){
            format = GL_RGBA;
        }else {
            cout<<"Fatal error"<<endl;
        }
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLuint texture;
        glGenTextures ( 1 , &texture);
        glBindTexture ( GL_TEXTURE_2D , texture);

        GLint param1, param2, efecto = 1; // - efecto de 0 a 3 --
        switch( efecto ){
          case 0:  param2 = GL_NEAREST; param1 = GL_NEAREST; break;
          case 1:  param2 = GL_LINEAR;  param1 = GL_LINEAR; break;
          case 2:  param2 = GL_LINEAR;  param1 = GL_NEAREST_MIPMAP_NEAREST; break;
          case 3:  param2 = GL_LINEAR;  param1 = GL_LINEAR_MIPMAP_LINEAR; break;
          default: param2 = GL_NEAREST; param1 = GL_NEAREST; break;
        }
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param1 );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2 );
        glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w,  surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
        
        return texture;
    }
    void blit_texture(GLuint texture,int x,int y,int w,int h,int rx,int ry){
        int xcenter = x + w/2; int ycenter = y + h/2;
        glBindTexture( GL_TEXTURE_2D, texture );
        glEnable( GL_TEXTURE_2D );
        glPushMatrix();
        glTranslatef(xcenter, ycenter, 1);
        glRotatef(0, 0, 0, 1);
        glTranslatef(-xcenter, -ycenter, -1);
        glBegin(GL_QUADS);
            glLoadIdentity ();
            glTexCoord2f(   0,   0 );  glVertex2f(x    ,  y );
            glTexCoord2f(rx  ,   0 );  glVertex2f(x + w,  y );
            glTexCoord2f(rx  ,  -ry);  glVertex2f(x + w,  y + h);
            glTexCoord2f(0   ,  -ry);  glVertex2f(x    ,  y + h);
        glEnd();
        glPopMatrix();

        glDisable( GL_TEXTURE_2D );
    }
    void blit_texture_rotated(GLuint texture,int x,int y,int w,int h,int angle){ //  La posicion X e Y van a ser el centro
        glBindTexture( GL_TEXTURE_2D, texture );
        glEnable( GL_TEXTURE_2D );
        glPushMatrix();
        glTranslatef(x, y, 1);
        glRotatef(angle, 0, 0, 1);
        glBegin(GL_QUADS);
        glLoadIdentity ();
        glTexCoord2f(   0,   0 );  glVertex2f(-w/2    ,  -h/2 );
        glTexCoord2f(1  ,   0 );  glVertex2f(-w/2 + w,  -h/2 );
        glTexCoord2f(1  ,  1);  glVertex2f(-w/2 + w,  -h/2 + h);
        glTexCoord2f(0   ,  1);  glVertex2f(-w/2    ,  -h/2 + h);
        glEnd();
        glPopMatrix();
        
        glDisable( GL_TEXTURE_2D );
    }
    void simple_blit(SDL_Surface* surface,int x,int y){

        int w = surface->w;
        int h = surface->h;

        int mode,bit;

        if (surface->format->BytesPerPixel == 3) { // RGB 24bit
           bit = 24;
           mode = GL_RGB;
        }else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
           bit = 32;
           mode = GL_RGBA;
        }

        //glColor3ub (255,255,255);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        unsigned Texture = 0;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,  h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

        glBegin(GL_QUADS);
           glLoadIdentity ();
           glTexCoord2f(0,0);  glVertex2f(x    ,  y );
           glTexCoord2f(1,0);  glVertex2f(x + w,  y );
           glTexCoord2f(1,-1); glVertex2f(x + w,  y + h);
           glTexCoord2f(0,-1); glVertex2f(x    ,  y + h);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(1,&Texture);
    }

    void blit(SDL_Surface* surface,int x,int y, double angle, int w, int h){
        if (w == NO_NUMBER){
            w = surface->w;
        }
        if (h == NO_NUMBER){
            h = surface->h;
        }
        glColor3ub(255,255,255);
        unsigned texture = 0;

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

        glPushMatrix();
        if (angle != 0){
            glRotatef(angle, 0, 0, 1);
        }else{
            x += w/2;
            y += h/2;
        }
        int cx,cy,sx,sy;
        w /= 2; h /= 2;
        cx = cos(angle*PI/180)*w;
        cy = cos(angle*PI/180)*h;
        sx = sin(angle*PI/180)*w;
        sy = sin(angle*PI/180)*h;
        w = MAX((int)ceil(MAX(MAX(MAX(fabs(cx + sy), fabs(cx - sy)), fabs(-cx + sy)), fabs(-cx - sy))), 1);
        h = MAX((int)ceil(MAX(MAX(MAX(fabs(sx + cy), fabs(sx - cy)), fabs(-sx + cy)), fabs(-sx - cy))), 1);
        w *= 2; h *= 2;
        glTranslatef(x,y,0);
        /*w /= 2;
        h /= 2;*/
        glBegin(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3d(0 ,0  ,0.0f);
        glTexCoord2f(1,0);  glVertex3d(w  ,0  ,0.0f);
        glTexCoord2f(1,-1);  glVertex3d(w  ,h ,0.0f);
        glTexCoord2f(0,-1); glVertex3d(0 ,h ,0.0f);
        glEnd();
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glDeleteTextures(1,&texture);
    }
    void gl_blit_texture(GLuint texture, int x, int y, int w, int h){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glVertex2f(x-w/2, y-h/2);
        glVertex2f(x+w/2, y-h/2);
        glVertex2f(x+w/2, y+h/2);
        glVertex2f(x-w/2, y+h/2);

        glEnd();

        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(1, &texture);
    }
    void blit_text(TTF_Font* font, string text, SDL_Color color, int x, int y){
        SDL_Surface* surface = TTF_RenderText_Blended(font,text.c_str(),color);
        GLuint tex = generate_texture(surface);
        blit_texture(tex, x, y, surface->w, surface->h);
        SDL_FreeSurface(surface);
        glDeleteTextures(1,&tex);
    }
    void blit_surface_inside_another(SDL_Surface* source, SDL_Surface* destination, int x, int y){
        SDL_Rect where;
        where.x = x;
        where.y = y;
        SDL_BlitSurface(source,NULL,destination,&where);
    }
    SDL_Surface* repeat_surface(SDL_Surface* root,int ax,int ay){

        int w = root->w;
        int h = root->h;
        SDL_Surface* nueva = OGL::create_void_surface ( ax * w , ay * h );
        for (int x = 0;x < ax;x++){
            for (int y = 0;y < ay;y++){
                OGL::blit_surface_inside_another (root,nueva,x*w,y*h);
            }
        }
        return nueva;
    }
}
