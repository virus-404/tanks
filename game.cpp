#include "./opengl.h"
#include "board.cpp"
#include "tank.cpp"

using namespace std;

int keyflag = 0;
long last_t = 0;
int anglealpha = 0;
int anglebeta = 0;

Board *board;
Tank *player;
Tank *enemy;

void display();
void keyboard(unsigned char, int, int);
void positionObserver(float alpha, float beta, int radi);
void idle();
bool checkWall(int, int);
bool checkPlayerGoal(int, int);
bool checkEnemyGoal(int, int);
void moveEnemy();
void swap(int &a, int &b);

int main(int argc, char *argv[]) {
    board = new Board(COLUMNS, ROWS);
    player = new Tank(new float[3]{0.20, 0.80, 0.20}, 'P');
    enemy = new Tank(new float[3]{0.83, 0.00, 0.00}, 'E');
    anglealpha = 90;
    anglebeta = 30;

    player->set_position(1, ROWS - 2);
    board->setPositionBoard(1, ROWS - 2, 'P');
    enemy->set_position(COLUMNS - 2, 1);
    board->setPositionBoard(COLUMNS - 2, 1, 'E');

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tanks board");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glBindTexture(GL_TEXTURE_2D, 0);
    glutMainLoop();
    return 0;
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    positionObserver(anglealpha, anglebeta, 450);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH * 0.5, WIDTH * 0.5, -HEIGHT * 0.5, HEIGHT * 0.5, 10, 1000);
    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    board->draw();
    player->draw();
    enemy->draw();

    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
    if (player->get_state() == MOVE) return;
    if (c == 'w')
        player->keyPressed(c, board);  // UP
    else if (c == 'd')
        player->keyPressed(c, board);  // RIGHT
    else if (c == 'a')
        player->keyPressed(c, board);  // LEFT
    else if (c == 's')
        player->keyPressed(c, board);  // DOWN
    else if (c == 'i' && anglebeta <= (90 - 4))
        anglebeta = (anglebeta + 3);
    else if (c == 'k' && anglebeta >= (-90 + 4))
        anglebeta = anglebeta - 3;
    else if (c == 'j')
        anglealpha = (anglealpha + 3) % 360;
    else if (c == 'l')
        anglealpha = (anglealpha - 3 + 360) % 360;
    glutPostRedisplay();
}

void positionObserver(float alpha, float beta, int radi) {
    float x, y, z;
    float upx, upy, upz;
    float modul;

    x = (float)radi * cos(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
    y = (float)radi * sin(beta * 2 * PI / 360.0);
    z = (float)radi * sin(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);

    if (beta > 0) {
        upx = -x;
        upz = -z;
        upy = (x * x + z * z) / y;
    } else if (beta == 0) {
        upx = 0;
        upy = 1;
        upz = 0;
    } else {
        upx = x;
        upz = z;
        upy = -(x * x + z * z) / y;
    }

    modul = sqrt(upx * upx + upy * upy + upz * upz);

    upx = upx / modul;
    upy = upy / modul;
    upz = upz / modul;

    gluLookAt(x, y, z, 0.0, 0.0, 0.0, upx, upy, upz);
}

void moveEnemy() {
    if (enemy->get_state() == MOVE) return;
    int direction[4];
    direction[0] = 0;  // w
    direction[1] = 1;  // d
    direction[2] = 2;  // a
    direction[3] = 3;  // s

    switch (direction[rand() & 3]) {
        case 0:
            enemy->keyPressed('w', board);
            break;
        case 1:
            enemy->keyPressed('d', board);
            break;
        case 2:
            enemy->keyPressed('a', board);
        case 3:
            enemy->keyPressed('s', board);
            break;
    }
}

void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void idle() {
    long t;

    t = glutGet(GLUT_ELAPSED_TIME);
    moveEnemy();
    if (last_t == 0)
        last_t = t;
    else {
        player->integrate(t - last_t);
        enemy->integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}
