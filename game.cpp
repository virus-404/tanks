#include <iostream>

#include "board.cpp"
#include "opengl.h"
#include "tank.cpp"

using namespace std;

int keyflag = 0;  // It is needed a cell width as a translation of a tank.
int cell_width = WIDTH / COLUMNS;
int cell_heigth = HEIGHT / ROWS;
long last_t = 0;

Board *board;
Tank *player;
Tank *enemy;

void display();
void keyboard(unsigned char, int, int);
void idle();
bool checkWall(int, int);
bool checkPlayerGoal(int, int);
bool checkEnemyGoal(int, int);
void moveEnemy();
void swap(int &a, int &b);

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
    // TODO: movement??
    float movement = 1;
    float nextXPlayer;
    float nextYPlayer;
    // UP
    if (c == 'w') {
        nextXPlayer = player->getX_CurrentPosition();
        nextYPlayer = player->getY_CurrentPosition() + movement;
        if (checkWall(nextXPlayer, nextYPlayer))
        {
            player->init_movement(nextXPlayer, nextYPlayer, 1000);
        }
        if (checkPlayerGoal(nextXPlayer, nextYPlayer))
        {
            // Player wins
            // End game or reset game
        }
    }
    // RIGHT
    else if (c == 'd') {
        nextXPlayer = player->getX_CurrentPosition() + movement;
        nextYPlayer = player->getY_CurrentPosition();
        if (checkWall(nextXPlayer, nextYPlayer))
        {
            player->init_movement(nextXPlayer, nextYPlayer, 1000);
        }
        if (checkPlayerGoal(nextXPlayer, nextYPlayer))
        {
            // Player wins
            // End game or reset game
        }
    // LEFT
    } else if (c == 'a') {
        nextXPlayer = player->getX_CurrentPosition() - movement;
        nextYPlayer = player->getY_CurrentPosition();
        if (checkWall(nextXPlayer, nextYPlayer))
        {
            player->init_movement(nextXPlayer, nextYPlayer, 1000);
        }
        if (checkPlayerGoal(nextXPlayer, nextYPlayer))
        {
            // Player wins
            // End game or reset game
        }
    // DOWN
    } else if (c == 's') {
        nextXPlayer = player->getX_CurrentPosition();
        nextYPlayer = player->getY_CurrentPosition() - movement;
        if (checkWall(nextXPlayer, nextYPlayer))
        {
            player->init_movement(nextXPlayer, nextYPlayer, 1000);
        }
        if (checkPlayerGoal(nextXPlayer, nextYPlayer))
        {
            // Player wins
            // End game or reset game
        }
    }

    moveEnemy();

    glutPostRedisplay();
}

void moveEnemy() {
    int direction[4];
    direction[0] = 0; // UP
    direction[1] = 1; // RIGHT
    direction[2] = 2; // LEFT
    direction[3] = 3; // DOWN

    for (int i = 0; i < 4; i++) {
        int r = rand() & 3;
        swap(direction[r], direction[i]);
    }

    // TODO: movement??
    float movement = 1;
    float nextXEnemy;
    float nextYEnemy;

    switch (direction[rand()&3]) {
        case 0:
            nextXEnemy= enemy->getX_CurrentPosition();
            nextYEnemy = enemy->getY_CurrentPosition() + movement;
            if (checkWall(nextXEnemy, nextYEnemy))
            {
                enemy->init_movement(nextXEnemy, nextYEnemy, 1000);
            }
            if (checkEnemyGoal(nextXEnemy, nextYEnemy))
            {
                // Enemy wins, Player loses
                // End game or reset game
            }
            break;
        case 1:
            nextXEnemy = enemy->getX_CurrentPosition() + movement;
            nextYEnemy = enemy->getY_CurrentPosition();
            if (checkWall(nextXEnemy, nextYEnemy))
            {
                enemy->init_movement(nextXEnemy, nextYEnemy, 1000);
            }
            if (checkEnemyGoal(nextXEnemy, nextYEnemy))
            {
                // Enemy wins, Player loses
                // End game or reset game
            }
            break;
        case 2:
            nextXEnemy = enemy->getX_CurrentPosition() - movement;
            nextYEnemy = enemy->getY_CurrentPosition();
            if (checkWall(nextXEnemy, nextYEnemy))
            {
                enemy->init_movement(nextXEnemy, nextYEnemy, 1000);
            }
            if (checkEnemyGoal(nextXEnemy, nextYEnemy))
            {
                // Enemy wins, Player loses
                // End game or reset game
            }
            break;
        case 3:
            nextXEnemy = enemy->getX_CurrentPosition();
            nextYEnemy = enemy->getY_CurrentPosition() - movement;
            if (checkWall(nextXEnemy, nextYEnemy))
            {
                enemy->init_movement(nextXEnemy, nextYEnemy, 1000);
            }
            if (checkEnemyGoal(nextXEnemy, nextYEnemy))
            {
                // Enemy wins, Player loses
                // End game or reset game
            }
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

    if (last_t == 0)
        last_t = t;
    else {
        player->integrate(t - last_t);
        enemy->integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}

bool checkWall(int x, int y) {
	// if not a wall return true
    return board->map[x][y] == ' ';
}

bool checkPlayerGoal(int x, int y) {
    return x == board->getEnemyRespawnPoint_X() && y == board->getEnemyRespawnPoint_Y();
}

bool checkEnemyGoal(int x, int y) {
    return x == board->getPlayerRespawnPoint_X() && y == board->getPlayerRespawnPoint_Y();
}
