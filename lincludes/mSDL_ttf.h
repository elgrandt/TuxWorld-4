#ifndef mSDL_TTF_H_
#define mSDL_TTF_H_

#ifdef __APPLE__
    #include <SDL2_ttf/SDL_ttf.h>
#elif defined __linux__
    #include "SDL2/SDL_ttf.h"
#elif defined _WIN32 || defined _WIN64
    #include "SDL_ttf.h"
#endif

#endif
