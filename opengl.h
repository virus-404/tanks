#ifdef __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
    #define GL_SILENCE_DEPRECATION
#else
    #error "OS not supported!"
#endif

#define MOVE 1
#define QUIET 2
