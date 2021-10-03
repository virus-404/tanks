#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define MOVE 1
#define QUIET 2

using namespace std;

class TankPlayer {
    private:
        float x,y;   //-- Current position
        float vx,vy; //-- Velocity vector
        int state;
        long time_remaining;
    
    public:
        void tankPlayer();
        float getX_CurrentPosition();
        float getY_CurrentPosition();
        int get_state();
        void set_position(int x, int y);
        void init_movement(int destination_x, int destination_y, int duration);
        void integrate(long t);
        void draw();
};

float TankPlayer::getX_CurrentPosition() {
    return this->x;
}

float TankPlayer::getY_CurrentPosition() {
    return this->y;
}

int TankPlayer::get_state() {
    return this->state;
}

void TankPlayer::tankPlayer() {
    this->state = QUIET;
}

// Set initial position of the player.
void TankPlayer::set_position(int x, int y) {
    this->x = x;
    this ->y = y;
}

void TankPlayer::init_movement(int destination_x, int destination_y, int duration) {
    this->vx = (destination_x - x) / duration;
    this->vy = (destination_y - y) / duration;
    this->state = MOVE;
    this->time_remaining = duration;
}

// Update player's position according to the elapsed time t.
void TankPlayer::integrate(long t) {
    if (state == MOVE && t < time_remaining) {
        x = x + vx*t;
        y = y + vy*t;
        time_remaining -= t;
    }
    else if (state == MOVE && t >= time_remaining) {
        x = x + vx*time_remaining;
        y = y + vy*time_remaining;
        state = QUIET;
    }
}

void TankPlayer::draw() {
    // Green color for the player.
    glColor3f(0,255,30);
    glBegin(GL_QUADS);
    glVertex2i(x-6,y-6);
    glVertex2i(x+6,y-6);
    glVertex2i(x+6,y+6);
    glVertex2i(x-6,y+6);
    glEnd();
}
