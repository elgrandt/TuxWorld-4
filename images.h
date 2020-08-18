#ifndef IMAGES_H_
#define IMAGES_H_

#include <vector>
#include <map>

#include "lincludes/mSDL.h"
#include "lincludes/mSDL_ttf.h"
#include "lincludes/mSDL_image.h"

#include "OGL/OGL.h"

using namespace std;

struct Image{
    GLint img;
    SDL_Surface* surface;
    double w;
    double h;
};

namespace images{
    extern vector <SDL_Surface*> img;
    extern SDL_Surface* imagetest;
    extern SDL_Surface* window;

    /*** Widow pre-image codes ***/
    namespace window_images{
        namespace up{
            extern SDL_Surface* left_window;
            extern SDL_Surface* window;
            extern SDL_Surface* right_window;
        }
        namespace down{
            extern SDL_Surface* left_window;
            extern SDL_Surface* window;
            extern SDL_Surface* right_window;
        }

        namespace middle{
            extern SDL_Surface* left_window;
            extern SDL_Surface* window;
            extern SDL_Surface* right_window;
        }
        namespace buttons{
            extern SDL_Surface* red;
        }
        namespace alternative{
            extern SDL_Surface* redtop;
        }
        namespace redtop{
            extern SDL_Surface* left_window;
            extern SDL_Surface* window;
            extern SDL_Surface* right_window;
        }

    }

    /*End*/


    /*** GAME IMAGE codes ***/
    extern vector <Image> tux;
    extern vector <Image> tux_caminando_costado;
    extern vector <Image> tux_caminando_costado_b;
    extern vector <Image> tux_arriba;
    extern vector <Image> tux_cargando;
    extern vector <Image> final_tux_cargando;

    namespace wall{
        extern Image normal;
        extern Image d90;
        extern Image esquina;
    }
    namespace enemies{
        extern vector <Image> classical;
        extern Image windows;
        extern Image enorme;
    }
    namespace background{
        extern Image classic;
    }
    namespace money{
        extern Image cent;
        extern Image unit;
        extern Image units;
        extern Image units7;
        extern Image units9;
        extern Image malet;
        extern Image malet3;
        extern Image malet4;
        extern Image check;
        extern Image check2;
    }

    extern map <string , Image> check_point_text;

    extern vector <Image> check_point;
    extern Image check_point_image;

    /*End*/
}
namespace fonts{
    extern TTF_Font* bebas_neue;
    extern TTF_Font* bebas_neue_mini;
    extern TTF_Font* ubuntu_c;
    extern TTF_Font* calibri_c;
    extern TTF_Font* presentacion;
}
namespace cursors{
    extern SDL_Cursor* cursor;
    extern SDL_Cursor* hand;
    extern SDL_Cursor* close;
    extern SDL_Cursor* downright;
}

void load();

#endif // IMAGES_H_

