#ifndef mSDL_IMAGE_H_
#define mSDL_IMAGE_H_

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#elif defined __linux__
    #include "SDL2/SDL_image.h"
#elif defined _WIN32 || defined _WIN64
    #include "SDL_image.h"
#endif

#endif
