#include "../opengl.h"

class Cylinder {
   private:
    int length, section;
    float *coordinates;
    GLfloat angle;
    float *angelNorm;
    int rotation;

   public:
    Cylinder(){};
    void setLength(int);
    void setSection(int);
    void setCoordinates(float, float, float);
    void setOrientation(float, float[3]);
    void draw();
};

void Cylinder::setLength(int length) {
    this->length = length;
}
void Cylinder::setSection(int section) {
    this->section = section;
}
void Cylinder::setCoordinates(float x, float y, float z) {
    this->coordinates = new float[3]{x, y, z};
}
void Cylinder::setOrientation(float alpha, float angleNorm[3]) {
    this->angle = alpha;
    this->angelNorm = angleNorm;
}

void Cylinder::draw() {
    /*
        1) glPushMatrix();          //save the current matrix
        2) glTranslatef(0, 0, 90);  //move to the desired location
        3) draw-whatever();
        4) glPopMatrix();           //restore the old matrix
    */

    static GLUquadric *gluQuadric = NULL;  //"Context" to draw circle based polygons
    if (gluQuadric == NULL)
        gluQuadric = gluNewQuadric();

    glPushMatrix();
    
    glTranslatef(coordinates[0], coordinates[1], coordinates[2]);
    glRotatef(angle, angelNorm[0], angelNorm[1], angelNorm[2]);
   
    glColor3f(1, 0, 1);  //Base black
    gluDisk(gluQuadric, 0, section, 10, 1);  //inner = 0 --> No hollow
    glColor3f(0, 1, 1);  //Walls black
    gluCylinder(gluQuadric, section, section, length, 200, 200);
    glColor3f(0, 0, 1);  //Top black
    glTranslatef(0, 0, length);
    gluDisk(gluQuadric, 0, section, 10, 1);

    glPopMatrix();


    

}
