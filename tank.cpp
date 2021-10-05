#include "./opengl.h"
#pragma once

using namespace std;

class Tank {
   private:
    float x, y;    //-- Current position
    float vx, vy;  //-- Velocity vector
    int state;
    long time_remaining;
    float *color;

   public:
    Tank(float *);
    float getX_CurrentPosition();
    float getY_CurrentPosition();
    int get_state();
    void set_position(int, int);
    void init_movement(int, int, int);
    void integrate(long);
    void draw();
};

Tank::Tank(float *color) {
    this->color = color;
    this->state = QUIET;
}

float Tank::getX_CurrentPosition() {
    return this->x;
}

float Tank::getY_CurrentPosition() {
    return this->y;
}

int Tank::get_state() {
    return this->state;
}

// Set initial position of the player.
void Tank::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

void Tank::init_movement(int destination_x, int destination_y, int duration) {
    this->vx = (destination_x - x) / duration;
    this->vy = (destination_y - y) / duration;
    this->state = MOVE;
    this->time_remaining = duration;
}

// Update player's position according to the elapsed time t.
void Tank::integrate(long t) {
    if (state == MOVE && t < time_remaining) {
        x = x + vx * t;
        y = y + vy * t;
        time_remaining -= t;
    } else if (state == MOVE && t >= time_remaining) {
        x = x + vx * time_remaining;
        y = y + vy * time_remaining;
        state = QUIET;
    }
}

void Tank::draw() {
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex2i(x - 6, y - 6);
    glVertex2i(x + 6, y - 6);
    glVertex2i(x + 6, y + 6);
    glVertex2i(x - 6, y + 6);
    glEnd();
}
