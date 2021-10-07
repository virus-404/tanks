#include "./opengl.h"

#include "board.cpp"
#include <cmath>

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
    Tank(float*, char);
    int get_state();
    void set_position(int, int);
    void init_movement(int, int, int);
    void integrate(long);
    void draw();
    void keyPressed(unsigned char, Board*);
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
        if (id == 'P') cout << "(" << x <<"," << y << ")" << endl;
    }
}

void Tank::draw() {
    float reductionFactor = 0.35;
    float w_blank = reductionFactor * WIDTH / COLUMNS;
    float h_blank = reductionFactor * HEIGHT / ROWS;
    glColor3f(this->color[0], this->color[1], this->color[2]);
    
    glBegin(GL_QUADS);
    glVertex2f(x * WIDTH / COLUMNS + w_blank, y * HEIGHT / ROWS + h_blank);
    glVertex2f((x + 1) * WIDTH / COLUMNS - w_blank, y * HEIGHT / ROWS + h_blank);
    glVertex2f((x + 1) * WIDTH / COLUMNS - w_blank, (y + 1) * HEIGHT / ROWS - h_blank);
    glVertex2f(x * WIDTH / COLUMNS + w_blank, (y + 1) * HEIGHT / ROWS - h_blank);
    glEnd();
}

void Tank::keyPressed(unsigned char key, Board* board) {
    int delta_x = 0; 
    int delta_y = 0; 

    if (key == 'w') delta_y = 1; 
    else if (key == 'd') delta_x = 1; 
    else if (key == 'a') delta_x = -1;
    else if (key == 's') delta_y = -1;
    
    if (board->isValid(this->x + delta_x, this->y + delta_y, this->id))
    {
        board->setPositionBoard(this->x + delta_x, this->y + delta_y, this->id);
        this->init_movement(this->x + delta_x, this->y + delta_y, 1000);
    }
    
}
