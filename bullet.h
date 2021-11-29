#ifndef BULLET_H
#define BULLET_H

class Cylinder;

class Bullet {
   private:
    float vx, vy;
    char shooter;
    long time_remaining;

   public:
    float x, y;
    int state;
    Bullet(float, float, char);
    void draw();
    void integrate(long);
    void initMovement(int, int, int);
};

#endif