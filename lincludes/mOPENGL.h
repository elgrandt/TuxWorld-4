#ifndef MOPENGL_H_
#define MOPENGL_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#elif defined __linux__
    #include "GL/gl.h"
    #include "GL/glu.h"
#elif defined _WIN32 || defined _WIN64
    #include "GL/glu.h"
#endif

#endif // MOPENGL_H_
