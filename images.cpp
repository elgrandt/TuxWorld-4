#include "images.h"

#include <iostream>
#include <csignal>
#include <sstream>
#include <cstdio>

#include "graphical.h"

#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"
#include "lincludes/mSDL_image.h"
#include "lincludes/mSDL_gfx.h"

#include "OGL/OGL.h"

#define RUTAIMG "data/images/"
#define RUTAFONT "data/fonts/"
#define concat(first, second) first second

using namespace std;

string its(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}

namespace images{
    vector <SDL_Surface*> img;
    SDL_Surface* imagetest;
    SDL_Surface* window;

    /*** Widow pre-image codes ***/
    namespace window_images{
        namespace up{
            SDL_Surface* left_window;
            SDL_Surface* window;
            SDL_Surface* right_window;
        }
        namespace down{
            SDL_Surface* left_window;
            SDL_Surface* window;
            SDL_Surface* right_window;
        }
        namespace middle{
            SDL_Surface* left_window;
            SDL_Surface* window;
            SDL_Surface* right_window;
        }
        namespace buttons{
            SDL_Surface* red;
        }
        namespace alternative{
            SDL_Surface* redtop;
        }
        namespace redtop{
            SDL_Surface* left_window;
            SDL_Surface* window;
            SDL_Surface* right_window;
        }
    }
    /*End*/

    /*** Image codes ***/
    vector <Image> tux;
    vector <Image> tux_caminando_costado;
    vector <Image> tux_caminando_costado_b;
    vector <Image> tux_arriba;
    vector <Image> tux_cargando;
    vector <Image> final_tux_cargando;

    namespace wall{
        Image normal;
        Image d90;
        Image esquina;
    }
    namespace enemies{
        vector <Image> classical;
        Image windows;
        Image enorme;
    }
    namespace background{
        Image classic;
    }
    namespace money{
        Image cent;
        Image unit;
        Image units;
        Image units7;
        Image units9;
        Image malet;
        Image malet3;
        Image malet4;
        Image check;
        Image check2;
    }
    vector <Image> check_point;
    map <string , Image> check_point_text;
    Image check_point_image;
}
namespace fonts{
    TTF_Font* bebas_neue;
    TTF_Font* bebas_neue_mini;
    TTF_Font* ubuntu_c;
    TTF_Font* calibri_c;
    TTF_Font* presentacion;
}
namespace cursors{
    SDL_Cursor* cursor;
    SDL_Cursor* hand;
    SDL_Cursor* close;
    SDL_Cursor* downright;
}
SDL_Surface* load_image(string directory){
    SDL_Surface* data = IMG_Load((RUTAIMG+directory).c_str());
    if (data == NULL){
        cout<<"Error cargando la imagen "<< directory <<endl;
        raise(SIGABRT);
    }
    return data;
}
SDL_Surface* load_zoom(string directory,double w,double h){
    SDL_Surface* image = load_image(directory);
    SDL_Surface* finale = zoomSurface (image , w , h , SMOOTHING_ON);
    SDL_FreeSurface(image);
    return finale;
}
Image load_texture_zoom(string directory,double w,double h){
    SDL_Surface* image = load_zoom (directory,w,h);

    if (image == NULL){
        cout<<"Error cargando la imagen "<< directory <<endl;
        //system("pause");
        raise(SIGABRT);
    }
    GLint texture = OGL::generate_texture(image);
    Image ret;
    ret.img = texture;
    ret.w = image->w;
    ret.h = image->h;
    ret.surface = image;
    return ret;
}

SDL_Surface* load_90(string directory){
    SDL_Surface* image = load_image(directory);
    SDL_Surface* final = rotateSurface90Degrees (image,1);

    //SDL_FreeSurface(image);
    return final;
}
Image load_texture_90(string directory){
    SDL_Surface* image = load_90(directory);
    if (image == NULL){
        cout<<"Error cargando la imagen "<< directory <<endl;
        raise(SIGABRT);
    }
    GLint texture = OGL::generate_texture(image);
    Image ret;
    ret.img = texture;
    ret.w = image->w;
    ret.h = image->h;
    ret.surface = image;
    return ret;
}

TTF_Font* load_ttf(string directory, int size){
    TTF_Font* font = TTF_OpenFont((RUTAFONT+directory).c_str(),size);
    if (font == NULL){
        cout<<"Error cargando fuentes: "<<RUTAFONT+directory<<endl;
        raise(SIGABRT);//system("pause");
    }
    return font;
}
Image write_text(TTF_Font* font, string text,SDL_Color color){
    SDL_Surface* render_text = TTF_RenderText_Blended(font,text.c_str(),color);
    GLint texture = OGL::generate_texture(render_text);
    Image ret;
    ret.w = render_text->w;
    ret.h = render_text->h;
    ret.surface = render_text;
    ret.img = texture;
    return ret;
}

void load(){
    TTF_Init();
    /**** GAME IMAGES ****/
    cout<<"Loading images"<<endl;

    /*** TUX IMAGES ***/

    load_texture_zoom("tux/tux1.png",1,1);

    images::tux.push_back(load_texture_zoom("tux/tux1.png",1,1));
    images::tux.push_back(load_texture_zoom("tux/tux_caminando1.png",1,1));
    images::tux.push_back(load_texture_zoom("tux/tux_caminando2.png",1,1));

    images::tux_arriba.push_back(load_texture_zoom("tux/tux2.png",1,1));
    images::tux_arriba.push_back(load_texture_zoom("tux/tux2_caminando1.png",0.75,0.75));
    images::tux_arriba.push_back(load_texture_zoom("tux/tux2_caminando2.png",0.75,0.75));

    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3.png",0.75,0.75));
    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3_caminando1.png",0.75,0.75));
    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3_caminando2.png",0.75,0.75));
    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3_caminando3.png",0.75,0.75));
    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3_caminando4.png",0.75,0.75));
    images::tux_caminando_costado.push_back(load_texture_zoom("tux/tux3_caminando5.png",0.75,0.75));

    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3.png",-0.75,0.75));
    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3_caminando1.png",-0.75,0.75));
    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3_caminando2.png",-0.75,0.75));
    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3_caminando3.png",-0.75,0.75));
    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3_caminando4.png",-0.75,0.75));
    images::tux_caminando_costado_b.push_back(load_texture_zoom("tux/tux3_caminando5.png",-0.75,0.75));

    images::tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargando1.png", 1, 1));
    images::tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargando2.png", 1, 1));
    images::tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargando3.png", 1, 1));
    images::tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargando4.png", 1, 1));
    images::tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargando5.png", 1, 1));

    images::final_tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargandoDeFrente.png",1,1));
    images::final_tux_cargando.push_back(load_texture_zoom("TuxCargando/TuxCargandoManosArriba.png",1,1));

    /*** END TUX IMAGES ***/
    images::wall::normal = load_texture_zoom("wall/paredTile.png",1.0,1.0);
    images::wall::d90    = load_texture_90  ("wall/paredTile.png");
    images::wall::esquina = load_texture_zoom("wall/esquina.png", 1.0, 1.0);

    /*** MONEY ***/

    images::money::cent   = load_texture_zoom ("money/cent.png",1,1);
    images::money::unit   = load_texture_zoom ("money/unit.png",1,1);
    images::money::units  = load_texture_zoom ("money/units.png",1,1);
    images::money::units7 = load_texture_zoom ("money/units7.png",1,1);
    images::money::units9 = load_texture_zoom ("money/units9.png",1,1);
    images::money::malet  = load_texture_zoom ("money/malet.png",1,1);
    images::money::malet3 = load_texture_zoom ("money/malet3.png",1,1);
    images::money::malet4 = load_texture_zoom ("money/malet4.png",1,1);
    images::money::check  = load_texture_zoom ("money/check.png",1,1);
    images::money::check2 = load_texture_zoom ("money/check2.png",1,1);

    images::check_point_image =  load_texture_zoom("Checkpoints/checkpoint.png",1,1);

    /**** WINDOW IMAGES ****/

    images::window_images::up::left_window  = load_image("window/up/left/window.png" );
    images::window_images::up::window       = load_image("window/int/up/window.png"  );
    images::window_images::up::right_window = load_image("window/up/right/window.png");

    images::window_images::middle::left_window  = load_image("window/int/left/window.png");
    images::window_images::middle::window       = load_image("window/int/center/window.png");
    images::window_images::middle::right_window = load_image("window/int/right/window.png");

    images::window_images::down::left_window  = load_image("window/down/left/window.png");
    images::window_images::down::window       = load_image("window/int/down/window.png");
    images::window_images::down::right_window = load_image("window/down/right/window.png");

    images::window_images::buttons::red = load_image("window/redbutton/window.png");

    images::window_images::alternative::redtop  = load_image("window/redwindow/window.png");

    images::window_images::redtop::left_window  = load_image("window/redwindow/left/window.png");
    images::window_images::redtop::window       = load_image("window/redwindow/middle/window.png");
    images::window_images::redtop::right_window = load_image("window/redwindow/right/window.png");

    for (int x = 0;x <= 27;x++){
        images::enemies::classical.push_back( load_texture_zoom ("enemigos/volatileenemy/robot_1_"+its(x)+".png",1,1) );
    }
    images::enemies::windows = load_texture_zoom("enemigos/windows.png",1,1);
    images::enemies::enorme = load_texture_zoom("enemigos/enemigo_x4.png",1,1);
    //images::background::classic = load_texture_zoom("back/classic.png",1,1);

    /*End*/

    /*** CHECK POINT ***/
    for (int x = 0;x <= 9;x++){
        images::check_point.push_back ( load_texture_zoom("Checkpoints/check_point_8_"+its(x)+".png",1,1) );
    }
    /*End*/

    /*** LOADING TESTING IMAGES ***/
    SDL_Surface* surface = OGL::create_filled_surface(400,400,OGL::c(100,100,200));
    //OGL::border_surface(surface,50,400,400);
    images::imagetest = surface;
    //images::window = load_image("ventana.png");//saca esto para poner la imagen de la ventana

    /*End*/


    /*** LOADING FONTS ***/
    fonts::bebas_neue = load_ttf("BebasNeue.ttf", 20);
    fonts::bebas_neue_mini = load_ttf("BebasNeue.ttf", 12);
    fonts::ubuntu_c = load_ttf("Ubuntu-B.ttf",12);
    fonts::calibri_c = load_ttf("Calibri.ttf",15);
    fonts::presentacion = load_ttf("Calibri.ttf", 50);
    /*END*/

    /*** Loading cursors*/
    cursors::cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursors::hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    cursors::close = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    cursors::downright = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);

    /*End*/

    /*** CHECKPOINT TEXT ***/

    images::check_point_text["c"] = write_text(fonts::calibri_c, "c", OGL::c (33,170,189));
    images::check_point_text["h"] = write_text(fonts::calibri_c, "h", OGL::c (33,170,189));
    images::check_point_text["e"] = write_text(fonts::calibri_c, "e", OGL::c (33,170,189));

    images::check_point_text["k"] = write_text(fonts::calibri_c, "k", OGL::c (33,170,189));

    images::check_point_text["p"] = write_text(fonts::calibri_c, "p", OGL::c (33,170,189));
    images::check_point_text["o"] = write_text(fonts::calibri_c, "o", OGL::c (33,170,189));
    images::check_point_text["i"] = write_text(fonts::calibri_c, "i", OGL::c (33,170,189));
    images::check_point_text["n"] = write_text(fonts::calibri_c, "n", OGL::c (33,170,189));
    images::check_point_text["t"] = write_text(fonts::calibri_c, "t", OGL::c (33,170,189));

    cout<<"Finished loading images"<<endl;
}
