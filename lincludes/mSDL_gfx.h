#ifndef MSDL_GFX_H
#define MSDL_GFX_H

#ifdef __APPLE__
    #include "SDL2_rotozoom.h"
#elif defined __linux__
    #include "SDL2_rotozoom.h"
#elif defined _WIN32 || defined _WIN64
    #include "SDL2_rotozoom.h"
#endif

#endif // MSDL_GFX_H
