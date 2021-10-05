#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 400

//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);
void idle();

//-----------------------------------------------

class particle {
  float x,y;   //-- Current position
  float vx,vy; //-- Velocity vector
  int state;

  long time_remaining;

public:

  particle();
  void set_position(int x,int y);
  void init_movement(int destination_x,int destination_y,int duration);
  void integrate(long t);
  void draw();
};


//-----------------------------------------------

particle::particle()
{
  state=QUIET;
}

//-----------------------------------------------

void particle::set_position(int x,int y)
{
  this->x = x;
  this->y = y;
}

//-----------------------------------------------

void particle::init_movement(int destination_x,int destination_y,int duration)
{
  vx = (destination_x - x)/duration;
  vy = (destination_y - y)/duration;

  state=MOVE;
  time_remaining=duration;
}

//-----------------------------------------------

void particle::integrate(long t)
{
  if(state==MOVE && t<time_remaining)
    {
      x = x + vx*t;
      y = y + vy*t;
      time_remaining-=t;
    }
  else if(state==MOVE && t>=time_remaining)
    {
      x = x + vx*time_remaining;
      y = y + vy*time_remaining;
      state=QUIET;
    }
}

//-----------------------------------------------

void particle::draw()
{
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glVertex2i(x-6,y-6);
  glVertex2i(x+6,y-6);
  glVertex2i(x+6,y+6);
  glVertex2i(x-6,y+6);
  glEnd();
}



//-----------------------------------------------
// -- MAIN
//-----------------------------------------------

particle square;
long last_t=0;

int main(int argc,char *argv[])
{
  srand(time(NULL));
  square.set_position(50,50);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Variable Frame Rate");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,WIDTH-1,0.0,HEIGHT-1);

  glutMainLoop();
  return 0;
}


//-----------------------------------------------
//-----------------------------------------------
void display()
{
  glClearColor(0,0,0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  square.draw();

  glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  square.set_position(50,50);
  square.init_movement(WIDTH-50,HEIGHT-50,1000);

  glutPostRedisplay();
};


//-----------------------------------------------
//-----------------------------------------------
void idle()
{
  long t;

  t=glutGet(GLUT_ELAPSED_TIME); 

  if(last_t==0)
    last_t=t;
  else
    {
      square.integrate(t-last_t);
      last_t=t;
    }


  glutPostRedisplay();
}
