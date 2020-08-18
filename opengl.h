#ifndef INCLUDE_SDL_H_
#define INCLUDE_SDL_H_

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#elif defined __linux__ || defined _WIN32 || defined _WIN64
    #include "SDL2/SDL_image.h"
#endif

#endif
