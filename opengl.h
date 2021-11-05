#ifdef __linux__
#include <GL/glut.h>
#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#error "OS not supported!"
#endif

#include <cmath>
#include <iostream>

#define COLUMNS 30
#define ROWS 20
#define WIDTH 30
#define HEIGHT 30
#define HEIGHT_WALL 20

#define DISTANCE_UNIT 15  // 300/20 = 15
#define NUMBER_SUB_BLOCKS 16
#define DISTANCE_SUB_UNIT 0.9375  // 15/16 = 0.9375...
#define PI 3.141592653589793238462643383279502884197169

#define MOVE 1
#define QUIET 2
#define ROTATE 3

#pragma once
