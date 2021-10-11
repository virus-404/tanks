#include <GL/glut.h>
#include <math.h>

#define PI 3.1416

#define WIDTH 600
#define HEIGHT 400

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta = 0;

//-----------------------------------------------
//-----------------------------------------------

void PositionObserver(float alpha,float beta,int radi);

void display();
void keyboard(unsigned char c,int x,int y);


//-----------------------------------------------
//-----------------------------------------------

int main(int argc,char *argv[])
{
  anglealpha=90;
  anglebeta=30;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("3D Hello World");
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}

//-----------------------------------------------
//-----------------------------------------------

void PositionObserver(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}


//-----------------------------------------------
//-----------------------------------------------
void display()
{
  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  PositionObserver(anglealpha,anglebeta,450);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH*0.6,WIDTH*0.6,-HEIGHT*0.6,HEIGHT*0.6,10,2000);

  glMatrixMode(GL_MODELVIEW);

  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_LINE);

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3i(50,50,50);
  glVertex3i(-50,50,50);
  glVertex3i(-50,-50,50);
  glVertex3i(50,-50,50);
  glEnd();

  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3i(50,-50,-50);
  glVertex3i(-50,-50,-50);
  glVertex3i(-50,50,-50);
  glVertex3i(50,50,-50);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3i(50,-50,50);
  glVertex3i(50,-50,-50);
  glVertex3i(50,50,-50);
  glVertex3i(50,50,50);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3i(-50,50,50);
  glVertex3i(-50,50,-50);
  glVertex3i(-50,-50,-50);
  glVertex3i(-50,-50,50);
  glEnd();

  
 
  glutSwapBuffers();
}


//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  int i,j;

  if (c=='i' && anglebeta<=(90-4))
    anglebeta=(anglebeta+3);
  else if (c=='k' && anglebeta>=(-90+4))
    anglebeta=anglebeta-3;
  else if (c=='j')
    anglealpha=(anglealpha+3)%360;
  else if (c=='l')
    anglealpha=(anglealpha-3+360)%360;

  glutPostRedisplay();
}

