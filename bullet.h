#ifndef BULLET_H
#define BULLET_H

#include "assets/cylinder.h"

class Bullet {
   private:
    float vx, vy;
    char shooter;
    long time_remaining;

   public:
    float x, y;
    int state;
    char orientation;
    Bullet(float, float, char, char);
    void draw();
    void integrate(long);
    void initMovement(int, int, int);
};

#endif