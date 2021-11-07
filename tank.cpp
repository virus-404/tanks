#include <stdlib.h>

#include "assets/cylinder.cpp"
#include "board.cpp"
#include "opengl.h"

#define MAIN_GUN 0x0A
#define WHEEL 0x00

using namespace std;

class Tank {
   private:
    float x, y;    //-- Current position
    float vx, vy;  //-- Velocity vector
    float alpha;   //-- Current angle
    float w_angular;  //-- Angular speed;

    long time_remaining;
    float *color;
    char id, orientation;
    int state;
    int translationX;
    int translationY;
    int rotationX;
    int rotationY;
    int rotationAlpha;

    void initMovement(int, int, int);
    void initRotation(int, int);
    char getNextCardinal(bool);
    int  getFinalOrientation();
    void calcCoordinates(int[3]);
    void drawBox(int[][3]);
    void drawCylinder(int);
    int  mod(int, int);

   public:
    Tank(float *, char);
    int  getState();
    void setPosition(int, int);
    void setTranslation(int,int);
    void integrate(long);
    void draw();
    void keyPressed(unsigned char, Board *);
};

Tank::Tank(float *color, char id) {
    this->color = color;
    this->id = id;
    state = QUIET;
    orientation = 'E';
}

int Tank::getState() {
    return this->state;
}

// Set initial position of the player.
void Tank::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    alpha = 0; //Heding east
    orientation = 'E';
}

void Tank::initMovement(int destination_x, int destination_y, int duration) {
    vx = (destination_x - x) / duration;
    vy = (destination_y - y) / duration;
    state = MOVE;
    time_remaining = duration;
}

void Tank::initRotation(int destination_a, int duration) {
    w_angular = (destination_a - alpha) / duration;
    state = ROTATE;
    time_remaining = duration;
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
    } else if (state == ROTATE && t < time_remaining) {
        alpha = alpha + w_angular * t;
        time_remaining -= t;
    } else if (state == ROTATE && t >= time_remaining) {
        alpha = alpha + w_angular * t;
        time_remaining -= t;
        alpha = getFinalOrientation();
        state = QUIET;
    }
}
void Tank::keyPressed(unsigned char key, Board *board) {
    if (key == 'w') {
        int delta_x = 0;
        int delta_y = 0;

        switch (orientation) {
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

        if (board->isValid(x + delta_x, y + delta_y, id)) {
            board->setPositionBoard(x + delta_x, y + delta_y, id);
            initMovement(x + delta_x, y + delta_y, 1000);
        }
    
    } else {
        if (key == 'a') {
            orientation = getNextCardinal(false);
            initRotation(-90, 750);

        } else if (key == 'd') {
            orientation = getNextCardinal(true);
            initRotation(90, 750);
        }
    }
}

char Tank::getNextCardinal(bool clockwise){
    int length = 4;
    char cardinalDirection[4] = {'N', 'E', 'S', 'W'};
    char tmp = 'N';

    for (int i = 0; i < length; i++){
        if (orientation == cardinalDirection[i]){
            if (clockwise){
                tmp = cardinalDirection[mod((i + 1), length)];
            } else {
                tmp = cardinalDirection[mod((i - 1), length)];
            }
       }
    }
    return tmp;
}

int Tank::mod(int n, int m) {
    return (n % m + m) % m;
}

int Tank::getFinalOrientation() {
    if (orientation == 'N') {
        return 90;
    } else if (orientation == 'E') {
        return 0;
    } else if (orientation == 'S') {
        return 270;
    } else {
        return 180;
    }
    return -1;
}

void Tank::setTranslation(int translationX, int translationY){
    this->translationX = translationX;
    this->translationY = translationY;
}

void Tank::draw() {
    int edges = 8;
    int hull[edges][3] = {
        {4, 12, 8},   // a
        {4, 12, 2},   // b
        {4, 4, 2},    // c
        {4, 4, 8},    // d
        {12, 12, 8},  // e
        {12, 4, 8},   // f
        {12, 4, 2},   // g
        {12, 12, 2}   // h
    };

    int turret[edges][3] = {
        {6, 10, 12},  // a
        {6, 10, 8},   // b
        {6, 6, 8},    // c
        {6, 6, 12},   // d
        {10, 10, 12},  // e
        {10, 6, 12},   // f
        {10, 6, 8},    // g
        {10, 10, 8}    // h
    };

    for (int i = 0; i < edges; i++) {
        calcCoordinates(hull[i]);
        //calcCoordinates(turret[i]);
    }

    drawBox(hull);
    float *tmp = color;
    color = new float[3]{0.847, 0.847, 0.847};
    //drawBox(turret);
    color = tmp;

    for (int i = 0; i < 6; i++) drawCylinder(WHEEL + i);
    drawCylinder(MAIN_GUN);
}

void Tank::drawBox(int vertexes[8][3]) {
    glDisable(GL_TEXTURE_2D);

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[1][0], vertexes[1][1], vertexes[1][2]);
    glVertex3i(vertexes[2][0], vertexes[2][1], vertexes[2][2]);
    glVertex3i(vertexes[6][0], vertexes[6][1], vertexes[6][2]);
    glVertex3i(vertexes[7][0], vertexes[7][1], vertexes[7][2]);
    glEnd();

    
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[3][0], vertexes[3][1], vertexes[3][2]);
    glVertex3i(vertexes[5][0], vertexes[0][1], vertexes[0][2]);
    glVertex3i(vertexes[4][0], vertexes[5][1], vertexes[5][2]);
    glVertex3i(vertexes[0][0], vertexes[4][1], vertexes[4][2]);
    glEnd();

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[3][0], vertexes[3][1], vertexes[3][2]);
    glVertex3i(vertexes[0][0], vertexes[0][1], vertexes[0][2]);
    glVertex3i(vertexes[1][0], vertexes[1][1], vertexes[1][2]);
    glVertex3i(vertexes[2][0], vertexes[2][1], vertexes[2][2]);
    glEnd();

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[3][0], vertexes[3][1], vertexes[3][2]);
    glVertex3i(vertexes[2][0], vertexes[2][1], vertexes[2][2]);
    glVertex3i(vertexes[6][0], vertexes[6][1], vertexes[6][2]);
    glVertex3i(vertexes[5][0], vertexes[5][1], vertexes[5][2]);
    glEnd();

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[5][0], vertexes[5][1], vertexes[5][2]);
    glVertex3i(vertexes[6][0], vertexes[6][1], vertexes[6][2]);
    glVertex3i(vertexes[7][0], vertexes[7][1], vertexes[7][2]);
    glVertex3i(vertexes[4][0], vertexes[4][1], vertexes[4][2]);
    glEnd();

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3i(vertexes[0][0], vertexes[0][1], vertexes[0][2]);
    glVertex3i(vertexes[1][0], vertexes[1][1], vertexes[1][2]);
    glVertex3i(vertexes[7][0], vertexes[7][1], vertexes[7][2]);
    glVertex3i(vertexes[4][0], vertexes[4][1], vertexes[4][2]);
    glEnd();

    glEnable(GL_TEXTURE_2D);
}

void Tank::calcCoordinates(int vertexes [3]){
    //rotate phase
    int center[2] = {NUMBER_SUB_BLOCKS / 2, NUMBER_SUB_BLOCKS /2};

    double radius = sqrt(
        pow((double)vertexes[0] - center[0], 2) +
        pow((double)vertexes[1] - center[1], 2));  //pythagorean distance

    float beta = asin((vertexes[0] - center[0]) / radius); // Finding Beta which is the inital angle of the vertex respect to the 0º
    

    if (vertexes[0] < center[0] && vertexes[1] > center [1]) beta = beta + PI / 2; // transposing beta to the corresponding quadran
    else if (vertexes[0] < center[0] && vertexes[1] < center [1]) beta = beta + PI;
    else if (vertexes[0] > center[0] && vertexes[1] < center [1]) beta = beta + 3 * PI / 2; 
    
    cout << "X " << vertexes[0] << " Y  " << vertexes[1] << endl;
    vertexes[0] = (int) round(center[0] + radius * cos(beta + (alpha * PI / 180.00f)));   //paremetric circle equations for X + transformation degrees to radians
    vertexes[1] = (int) round(center[1] + radius * sin(beta + (alpha * PI / 180.00f)));    //paremetric circle equations for Y + transformation degrees to radians
    cout << "X " << vertexes[0] << " Y  " << vertexes[1] << endl;  
    cout << "-------------------------------------------------" << endl;
    //https:  //stackoverflow.com/questions/31502120/sin-and-cos-give-unexpected-results-for-well-known-angles

    //translate phase
    vertexes[0] = (vertexes[0] * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX;
    vertexes[1] = (vertexes[1] * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY;
    vertexes[2] = vertexes[2];
}

void Tank::drawCylinder(int part) {
    glDisable(GL_TEXTURE_2D);

    Cylinder *cyl = new Cylinder();

    switch (part) {
        case WHEEL:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (4.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (12.00f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                 4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case WHEEL + 1:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (8.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (12.00f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case WHEEL + 2:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (12.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (12.0f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                 4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case WHEEL + 3:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (4.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (1.90f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,  //for artifact issues
                4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case WHEEL + 4:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (8.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (1.90f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case WHEEL + 5:
            cyl->setLength(2);
            cyl->setSection(2);
            cyl->setCoordinates(
                (12.00f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (1.90f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                 4.00f);
            cyl->setInitAngle(90.0f, new float[3]{1.0f, 0.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
        case MAIN_GUN:
            cyl->setLength(5);
            cyl->setSection(2);
            cyl->setCoordinates(
                (10.0f * DISTANCE_SUB_UNIT) + x * DISTANCE_UNIT + translationX,
                (8.0f * DISTANCE_SUB_UNIT) + y * DISTANCE_UNIT + translationY,
                10.0f);
            cyl->setInitAngle(90.0f, new float[3]{0.0f, 1.0f, 0.0f});
            cyl->addRotationY(alpha);
            break;
    }
    cyl->draw();
    delete cyl;
    glEnable(GL_TEXTURE_2D);
}

