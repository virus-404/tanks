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
    int translationX = -(int)round(WIDTH / 2);   // WIDTH <--> COLUMNS
    int translationY = -(int)round(HEIGHT / 2);  // HEIGHT <--> ROWS

   public:
    Tank(float *, char);
    int get_state();
    void set_position(int, int);
    void init_movement(int, int, int);
    void integrate(long);
    void draw();
    void drawBox(int[][3]);
    void drawCylinder(int[][3]);
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
    int hull[8][3] = {
        {2, 14, 8},   // a
        {2, 14, 2},   // b
        {2, 3, 2},    // c
        {2, 3, 8},    // d
        {11, 14, 8},  // e
        {11, 3, 8},   // f
        {11, 3, 2},   // g
        {11, 14, 2}   // h
    };

    int turret[8][3] = {
        {4, 13, 12},   // a
        {4, 13, 8},    // b
        {4, 4, 8},     // c
        {4, 4, 12},    // d
        {8, 13, 12},   // e
        {8, 4, 12},    // f
        {8, 4, 8},     // g
        {8, 13, 8}     // h
    };

    drawBox(hull);
    float *tmp = this->color;
    this->color = new float[3]{0, 0, 0};
    drawBox(turret);
    this->color = tmp; 
}

void Tank::drawBox(int vertexes[8][3]) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[1][1]) + y * DISTANCE_UNIT + translationY, vertexes[1][2]);
    glVertex3i((vertexes[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[2][1]) + y * DISTANCE_UNIT + translationY, vertexes[2][2]);
    glVertex3i((vertexes[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[6][1]) + y * DISTANCE_UNIT + translationY, vertexes[6][2]);
    glVertex3i((vertexes[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[7][1]) + y * DISTANCE_UNIT + translationY, vertexes[7][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[3][1]) + y * DISTANCE_UNIT + translationY, vertexes[3][2]);
    glVertex3i((vertexes[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[0][1]) + y * DISTANCE_UNIT + translationY, vertexes[0][2]);
    glVertex3i((vertexes[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[5][1]) + y * DISTANCE_UNIT + translationY, vertexes[5][2]);
    glVertex3i((vertexes[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[4][1]) + y * DISTANCE_UNIT + translationY, vertexes[4][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[3][1]) + y * DISTANCE_UNIT + translationY, vertexes[3][2]);
    glVertex3i((vertexes[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[0][1]) + y * DISTANCE_UNIT + translationY, vertexes[0][2]);
    glVertex3i((vertexes[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[1][1]) + y * DISTANCE_UNIT + translationY, vertexes[1][2]);
    glVertex3i((vertexes[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[2][1]) + y * DISTANCE_UNIT + translationY, vertexes[2][2]);
    glEnd();
   
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[3][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[3][1]) + y * DISTANCE_UNIT + translationY, vertexes[3][2]);
    glVertex3i((vertexes[2][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[2][1]) + y * DISTANCE_UNIT + translationY, vertexes[2][2]);
    glVertex3i((vertexes[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[6][1]) + y * DISTANCE_UNIT + translationY, vertexes[6][2]);
    glVertex3i((vertexes[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[5][1]) + y * DISTANCE_UNIT + translationY, vertexes[5][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[5][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[5][1]) + y * DISTANCE_UNIT + translationY, vertexes[5][2]);
    glVertex3i((vertexes[6][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[6][1]) + y * DISTANCE_UNIT + translationY, vertexes[6][2]);
    glVertex3i((vertexes[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[7][1]) + y * DISTANCE_UNIT + translationY, vertexes[7][2]);
    glVertex3i((vertexes[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[4][1]) + y * DISTANCE_UNIT + translationY, vertexes[4][2]);
    glEnd();

    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_QUADS);
    glVertex3i((vertexes[0][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[0][1]) + y * DISTANCE_UNIT + translationY, vertexes[0][2]);
    glVertex3i((vertexes[1][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[1][1]) + y * DISTANCE_UNIT + translationY, vertexes[1][2]);
    glVertex3i((vertexes[7][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[7][1]) + y * DISTANCE_UNIT + translationY, vertexes[7][2]);
    glVertex3i((vertexes[4][0] * DISTANCE_SUBUNIT) + x * DISTANCE_UNIT + translationX, (vertexes[4][1]) + y * DISTANCE_UNIT + translationY, vertexes[4][2]);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void Tank::drawCylinder(int vertex[8][3]) {
}