#include "opengl.h"
#include "bullet.h"

Bullet::Bullet(float x, float y, char shooter) {
    this->x = x;
    this->y = y;
    this->shooter = shooter;
}

void Bullet::draw() {
    glDisable(GL_TEXTURE_2D);
    /*
    Cylinder *cyl = new Cylinder();

    cyl->setLength(2);
    cyl->setSection(1);
    cyl->setCoordinates(
        15.00f * DISTANCE_SUB_UNIT - CENTER_SUB_UNIT,
        8.00f * DISTANCE_SUB_UNIT - CENTER_SUB_UNIT,
        10.0f);
    cyl->setOrientation(90.0f, new float[3]{0.0f, 1.0f, 0.0f});

    cyl->draw();
    delete cyl;
    */
    glEnable(GL_TEXTURE_2D);
}

void Bullet::initMovement(int destination_x, int destination_y, int duration) {
    vx = (destination_x - x) / duration;
    vy = (destination_y - y) / duration;
    state = MOVE;
    time_remaining = duration;
}

void Bullet::integrate (long t) {
    if(state == MOVE && t < time_remaining) {
        x = x + vx * t;
        y = y + vy * t;
        time_remaining -= t;
    }
    else if (state == MOVE && t >= time_remaining) {
        x = x + vx * time_remaining;
        y = y + vy * time_remaining;
        state = QUIET;    
    }
}