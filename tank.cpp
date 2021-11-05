#include "opengl.h"
#include "board.cpp"
#include "assets/cylinder.cpp"

#define MAIN_GUN 0x0A
#define WHEEL 0x00

using namespace std;

class Tank {
   private:
    float x, y;    //-- Current position
    float vx, vy;  //-- Velocity vector
    long time_remaining;
    float *color;
    char id, orientation;
    int state;
    int translationX;
    int translationY;

   public:
    Tank(float *, char);
    int get_state();
    void set_position(int, int);
    void init_movement(int, int, int);
    void integrate(long);
    void setTranslation(int,int);
    void draw();
    void drawBox(int[][3]);
    void drawCylinder(int);
    void keyPressed(unsigned char, Board *);
};

Tank::Tank(float *color, char id) {
    this->color = color;
    this->state = QUIET;
    this->id = id;
    this->orientation = 'E';
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
    if (key == 'w') {
        int delta_x = 0;
        int delta_y = 0;

        switch (this->orientation) {
            case 'N':
                delta_y = 1;
                break;
            case 'S':
                delta_y = -1;
                break;
            case 'E':
                delta_x = 1;
                break;
            case 'W':
                delta_x = -1;
                break;
        }

        if (board->isValid(this->x + delta_x, this->y + delta_y, this->id)) {
            board->setPositionBoard(this->x + delta_x, this->y + delta_y, this->id);
            this->init_movement(this->x + delta_x, this->y + delta_y, 1000);
        }
    } else if (key == 'a') {
        switch (this->orientation) {
            case 'N':
                this->orientation = 'W';
                break;
            case 'S':
                this->orientation = 'E';
                break;
            case 'E':
                this->orientation = 'N';
                break;
            case 'W':
                this->orientation = 'S';
                break;
        }
    } else if (key == 'd') {
        switch (this->orientation) {
            case 'N':
                this->orientation = 'E';
                break;
            case 'S':
                this->orientation = 'W';
                break;
            case 'E':
                this->orientation = 'S';
                break;
            case 'W':
                this->orientation = 'N';
                break;
        }
    }
}

void Tank::setTranslation(int translationX, int translationY){
    this->translationX = translationX;
    this->translationY = translationY;
}

void Tank::draw() {
    int edges = 8;
    int hull[edges][3] = {
        {4, 12, 8},   // a
        {4, 12, 3},   // b
        {4, 4, 3},    // c
        {4, 4, 8},    // d
        {12, 12, 8},  // e
        {12, 4, 8},   // f
        {12, 4, 3},   // g
        {12, 12, 2}   // h
    };

    int turret[edges][3] = {
        {6, 10, 12},   // a
        {6, 10, 8},    // b
        {6, 6, 8},     // c
        {6, 6, 12},    // d
        {10, 10, 12},  // e
        {10, 6, 12},   // f
        {10, 6, 8},    // g
        {10, 10, 8}    // h
    };

    drawBox(hull);
    float *tmp = this->color;
    this->color = new float[3]{0.847, 0.847, 0.847};
    drawBox(turret);
    this->color = tmp;

    for (int i = 0; i < 6; i++) drawCylinder(WHEEL + i);
    drawCylinder(MAIN_GUN);

    //move to center
    // rotate
    // move to previous position
}

    void Tank::drawBox(int vertexes[8][3]) {
        glDisable(GL_TEXTURE_2D);
        glColor3f(this->color[0], this->color[1], this->color[2]);  //+ x * DISTANCE_UNIT + translationX, + y * DISTANCE_UNIT + translationY
        glBegin(GL_QUADS);
        glVertex3i(vertexes[1][0] * DISTANCE_SUB_UNIT , vertexes[1][1] * DISTANCE_SUB_UNIT , vertexes[1][2]);
        glVertex3i(vertexes[2][0] * DISTANCE_SUB_UNIT , vertexes[2][1] * DISTANCE_SUB_UNIT , vertexes[2][2]);
        glVertex3i(vertexes[6][0] * DISTANCE_SUB_UNIT , vertexes[6][1] * DISTANCE_SUB_UNIT , vertexes[6][2]);
        glVertex3i(vertexes[7][0] * DISTANCE_SUB_UNIT , vertexes[7][1] * DISTANCE_SUB_UNIT , vertexes[7][2]);
        glEnd();

        glColor3f(this->color[0], this->color[1], this->color[2]);
        glBegin(GL_QUADS);
        glVertex3i(vertexes[3][0] * DISTANCE_SUB_UNIT , vertexes[3][1] * DISTANCE_SUB_UNIT , vertexes[3][2]);
        glVertex3i(vertexes[5][0] * DISTANCE_SUB_UNIT , vertexes[0][1] * DISTANCE_SUB_UNIT , vertexes[0][2]);
        glVertex3i(vertexes[4][0] * DISTANCE_SUB_UNIT , vertexes[5][1] * DISTANCE_SUB_UNIT , vertexes[5][2]);
        glVertex3i(vertexes[0][0] * DISTANCE_SUB_UNIT , vertexes[4][1] * DISTANCE_SUB_UNIT , vertexes[4][2]);
        glEnd();

        glColor3f(this->color[0], this->color[1], this->color[2]);
        glBegin(GL_QUADS);
        glVertex3i(vertexes[3][0] * DISTANCE_SUB_UNIT , vertexes[3][1] * DISTANCE_SUB_UNIT , vertexes[3][2]);
        glVertex3i(vertexes[0][0] * DISTANCE_SUB_UNIT , vertexes[0][1] * DISTANCE_SUB_UNIT , vertexes[0][2]);
        glVertex3i(vertexes[1][0] * DISTANCE_SUB_UNIT , vertexes[1][1] * DISTANCE_SUB_UNIT , vertexes[1][2]);
        glVertex3i(vertexes[2][0] * DISTANCE_SUB_UNIT , vertexes[2][1] * DISTANCE_SUB_UNIT , vertexes[2][2]);
        glEnd();

        glColor3f(this->color[0], this->color[1], this->color[2]);
        glBegin(GL_QUADS);
        glVertex3i(vertexes[3][0] * DISTANCE_SUB_UNIT , vertexes[3][1] * DISTANCE_SUB_UNIT , vertexes[3][2]);
        glVertex3i(vertexes[2][0] * DISTANCE_SUB_UNIT , vertexes[2][1] * DISTANCE_SUB_UNIT , vertexes[2][2]);
        glVertex3i(vertexes[6][0] * DISTANCE_SUB_UNIT , vertexes[6][1] * DISTANCE_SUB_UNIT , vertexes[6][2]);
        glVertex3i(vertexes[5][0] * DISTANCE_SUB_UNIT , vertexes[5][1] * DISTANCE_SUB_UNIT , vertexes[5][2]);
        glEnd();

        glColor3f(this->color[0], this->color[1], this->color[2]);
        glBegin(GL_QUADS);
        glVertex3i(vertexes[5][0] * DISTANCE_SUB_UNIT , vertexes[5][1] * DISTANCE_SUB_UNIT , vertexes[5][2]);
        glVertex3i(vertexes[6][0] * DISTANCE_SUB_UNIT , vertexes[6][1] * DISTANCE_SUB_UNIT , vertexes[6][2]);
        glVertex3i(vertexes[7][0] * DISTANCE_SUB_UNIT , vertexes[7][1] * DISTANCE_SUB_UNIT , vertexes[7][2]);
        glVertex3i(vertexes[4][0] * DISTANCE_SUB_UNIT , vertexes[4][1] * DISTANCE_SUB_UNIT , vertexes[4][2]);
        glEnd();

        glColor3f(this->color[0], this->color[1], this->color[2]);
        glBegin(GL_QUADS);
        glVertex3i(vertexes[0][0] * DISTANCE_SUB_UNIT , vertexes[0][1] * DISTANCE_SUB_UNIT , vertexes[0][2]);
        glVertex3i(vertexes[1][0] * DISTANCE_SUB_UNIT , vertexes[1][1] * DISTANCE_SUB_UNIT , vertexes[1][2]);
        glVertex3i(vertexes[7][0] * DISTANCE_SUB_UNIT , vertexes[7][1] * DISTANCE_SUB_UNIT , vertexes[7][2]);
        glVertex3i(vertexes[4][0] * DISTANCE_SUB_UNIT , vertexes[4][1] * DISTANCE_SUB_UNIT , vertexes[4][2]);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }

    void Tank::drawCylinder(int part) {
        glDisable(GL_TEXTURE_2D);

        Cylinder *cyl = new Cylinder();
        switch (part) {
            case WHEEL:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    4.00f * DISTANCE_SUB_UNIT,
                    14.00f * DISTANCE_SUB_UNIT,
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case WHEEL + 1:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    8.00f * DISTANCE_SUB_UNIT,
                    14.00f * DISTANCE_SUB_UNIT,
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case WHEEL + 2:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    12.00f * DISTANCE_SUB_UNIT,
                    14.00f * DISTANCE_SUB_UNIT,
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case WHEEL + 3:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    4.00f * DISTANCE_SUB_UNIT,
                    4.00f * DISTANCE_SUB_UNIT,  
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case WHEEL + 4:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    8.00f * DISTANCE_SUB_UNIT,
                    4.00f * DISTANCE_SUB_UNIT,
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case WHEEL + 5:
                cyl->setLength(2);
                cyl->setSection(2);
                cyl->setCoordinates(
                    12.00f * DISTANCE_SUB_UNIT,
                    4.00f * DISTANCE_SUB_UNIT,
                    4.00f);
                cyl->setOrientation(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
                break;
            case MAIN_GUN:
                cyl->setLength(5);
                cyl->setSection(1);
                cyl->setCoordinates(
                    10.00f * DISTANCE_SUB_UNIT,
                    8.00f * DISTANCE_SUB_UNIT,
                    10.0f);
                cyl->setOrientation(90.0f, new float[3]{0.0f, 1.0f, 0.0f});
                break;
        }
        cyl->draw();
        delete cyl;

        glEnable(GL_TEXTURE_2D);
    }
