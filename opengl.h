#ifdef __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #error "OS not supported!"
#endif

#define COLUMNS 20
#define ROWS 20
#define WIDTH 300
#define HEIGHT 300

#define MOVE 1
#define QUIET 2
#pragma once
