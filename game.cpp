#include <iostream>

#include "board.cpp"
#include "opengl.h"
#include "tank.cpp"

using namespace std;

int keyflag = 0;  // It is needed a cell width as a translation of a tank.
int cell_width;
long last_t = 0;

Board *board;
Tank *player;
Tank *enemy;

void display();
void keyboard(unsigned char, int, int);
void idle();
void drawTank(Tank *, int, int);

int main(int argc, char *argv[]) {
    board = new Board(COLUMNS, ROWS);
    player = new Tank(new float[3]{0.20, 0.80, 0.20});
    enemy = new Tank(new float[3]{0.83, 0.00, 0.00});
    player->set_position(1, ROWS - 2);
    enemy->set_position(COLUMNS - 2, 1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tanks board");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
    return 0;
}

void display() {
    int i, j;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (i = 0; i < board->map.size(); i++)
        for (j = 0; j < board->map[i].size(); j++)
            if (board->map[i][j] != ' ') {
                switch (board->map[i][j]) {
                    case 'E':
                        glColor3f(0.66, 0, 0);
                        break;
                    case 'P':
                        glColor3f(0.294, 0.325, 0.125);
                        break;
                    default:
                        glColor3f(0.8, 0.8, 0.8);
                        break;
                }

                glBegin(GL_QUADS);
                glVertex2i(i * WIDTH / COLUMNS, j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
                glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
                glEnd();
            }
    player->draw();
    enemy->draw();
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
    if (c == 'w') {
        player->init_movement(player->getX_CurrentPosition(), player->getY_CurrentPosition() + cell_width, 160);
    } else if (c == 'd') {
        player->init_movement(player->getX_CurrentPosition() + cell_width, player->getY_CurrentPosition(), 160);
    } else if (c == 'a') {
        player->init_movement(player->getX_CurrentPosition() - cell_width, player->getY_CurrentPosition(), 160);
    } else if (c == 's') {
        player->init_movement(player->getX_CurrentPosition(), player->getY_CurrentPosition() - cell_width, 160);
    }

    glutPostRedisplay();
}

void idle() {
    long t;

    t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0)
        last_t = t;
    else {
        player->integrate(t - last_t);
        enemy->integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}