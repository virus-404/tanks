#include <iostream>

#include "./opengl.h"
#include "./board.cpp"
#include "./tankPlayer.cpp"
#include "./tankEnemy.cpp"

#define COLUMNS 20
#define ROWS 20
#define WIDTH 300
#define HEIGHT 300


using namespace std;


int keyflag = 0;
// It is needed a cell width as a translation of a tank.
int cell_width;
long last_t = 0;


Board *board;
TankPlayer player;
TankEnemy enemy;


void display();
void keyboard(unsigned char c, int x, int y);
void idle();


int main(int argc, char *argv[])
{
    board = new Board(COLUMNS -2, ROWS -1); // -2 for borders
    // TODO: One square of the upper left quadrant of the maze needs to be corridor and connected with other corridors.
    // It is needed to save the initial position of the player as enemy's objective.
    //player.set_position(x_initPosPlayer, y_initPosPlayer);
    // TODO: One square of the lower right quadrant of the maze needs to be corridor and connected with other corridors.
    // It is needed to save the initial position of the enemy as player's objective.
    //enemy.set_position(x_initPosEnemy, y_initPosEnemy);
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


void display()
{
    int i, j;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (i = 0; i < board->map.size(); i++)
        for (j = 0; j < board->map[i].size(); j++)
            if (board->map[i][j] == 'X')
            {
                glColor3f(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);

                glVertex2i(i * WIDTH / COLUMNS, j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
                glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);

                glEnd();
            }
    glutSwapBuffers();
}


void keyboard(unsigned char c, int x, int y)
{
    if (c == 'w') {
        player.init_movement(player.getX_CurrentPosition(), player.getY_CurrentPosition() + cell_width, 160);
    }
    else if (c == 'd') {
        player.init_movement(player.getX_CurrentPosition() + cell_width, player.getY_CurrentPosition(), 160);
    }
    else if (c == 'a')
    {
        player.init_movement(player.getX_CurrentPosition() - cell_width, player.getY_CurrentPosition(), 160);
    }
    else if (c == 's') {
        player.init_movement(player.getX_CurrentPosition(), player.getY_CurrentPosition() - cell_width, 160);
    }
    
    glutPostRedisplay();
}


void idle() 
{
    long t;

    t = glutGet(GLUT_ELAPSED_TIME); 

    if (last_t == 0)
        last_t=t;
    else
    {
        player.integrate(t - last_t);
        enemy.integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}
