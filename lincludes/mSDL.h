#ifndef MSDL_H_
#define MSDL_H_

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#elif defined __linux__
    #include "SDL2/SDL.h"
#elif defined _WIN32 || defined _WIN64
    #include "SDL.h"
#endif

#endif //MSDL_H_
