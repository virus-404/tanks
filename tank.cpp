#include "./opengl.h"
#include "board.cpp"

using namespace std;

class Tank {
   private:
    float x, y;    //-- Current position
    float vx, vy;  //-- Velocity vector
    long time_remaining;
    float *color;
    char id;
    int state;

   public:
    Tank(float *, char);
    int get_state();
    void set_position(int, int);
    void init_movement(int, int, int);
    void integrate(long);
    void draw();
    void drawMainGun();
    void drawTurret();
    void drawWheels();
    void drawHull();

    void keyPressed(unsigned char, Board *);
};

Tank::Tank(float *color, char id) {
    this->color = color;
    this->state = QUIET;
    this->id = id;
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
        x = round(x);
        y = round(y);
        if (id == 'P') cout << "(" << x << "," << y << ")" << endl;
    }
}

void Tank::keyPressed(unsigned char key, Board *board) {
    int delta_x = 0;
    int delta_y = 0;

    if (key == 'w')
        delta_y = 1;
    else if (key == 'd')
        delta_x = 1;
    else if (key == 'a')
        delta_x = -1;
    else if (key == 's')
        delta_y = -1;

    if (board->isValid(this->x + delta_x, this->y + delta_y, this->id)) {
        board->setPositionBoard(this->x + delta_x, this->y + delta_y, this->id);
        this->init_movement(this->x + delta_x, this->y + delta_y, 1000);
    }
}

void Tank::draw() {
    drawMainGun();
    drawTurret();
    drawWheels();
    drawHull();
}

void Tank::drawHull() {
    int translationX = -(int)round(WIDTH / 2);   // WIDTH <--> COLUMNS
    int translationY = -(int)round(HEIGHT / 2);  // HEIGHT <--> ROWS

    int vertex[8][3] = {
        {2, 1, -7},   // a
        {2, 1, -10},  // b
        {2, 0, -10},  // c
        {2, 0, -7},   // d
        {11, 0, -7},   // e
        {11, 1, -7},   // f
        {11, 0, -10},  // g
        {11, 1, -10}   // h
    };

    

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[1][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
    glVertex3i((vertex[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[2][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
    glVertex3i((vertex[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[6][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
    glVertex3i((vertex[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[7][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[3][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
    glVertex3i((vertex[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[0][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
    glVertex3i((vertex[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[5][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
    glVertex3i((vertex[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[4][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[3][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
    glVertex3i((vertex[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[0][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
    glVertex3i((vertex[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[1][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
    glVertex3i((vertex[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[2][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
    glEnd();
   
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[3][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[3][2]);
    glVertex3i((vertex[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[2][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[2][2]);
    glVertex3i((vertex[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[6][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
    glVertex3i((vertex[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[5][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[5][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[5][2]);
    glVertex3i((vertex[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[6][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[6][2]);
    glVertex3i((vertex[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[7][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
    glVertex3i((vertex[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[4][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertex[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[0][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[0][2]);
    glVertex3i((vertex[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[1][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[1][2]);
    glVertex3i((vertex[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[7][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[7][2]);
    glVertex3i((vertex[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertex[4][1]) + y * DISTANCE_UNIT + translationY, HEIGHT_WALL * vertex[4][2]);
    glEnd();
}

void Tank::drawMainGun(){};
void Tank::drawWheels(){};
void Tank::drawTurret(){};
