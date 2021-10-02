#include <iostream>
#include <GL/glut.h>
#include "./board.cpp"

#define COLUMNS 20
#define ROWS 20
#define WIDTH 300
#define HEIGHT 300

using namespace std;

Board *board;
int keyflag = 0;

void display();
void keyboard(unsigned char c, int x, int y);

int main(int argc, char *argv[])
{
    board = new Board(COLUMNS -2, ROWS -1); // -2 for borders
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tanks board");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

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

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c, int x, int y)
{
    if (keyflag == 0)
        keyflag = 1;
    else
        keyflag = 0;

    glutPostRedisplay();
};
