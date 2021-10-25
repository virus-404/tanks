#include "../opengl.h"

class Cylinder {
   private:
    int length, section;
    float *posXYZ;
    GLfloat angle;
    float *angleXYZ;

   public:
    Cylinder(){};
    void setLength(int);
    void setSection(int);
    void setPosition(float, float, float);
    void setAngle(float);
    void setAngleNorm(float, float, float);
    void draw();
};

void Cylinder::setLength(int length) {
    this->length = length;
}
void Cylinder::setSection(int section) {
    this->section = section;
}
void Cylinder::setPosition(float x, float y, float z) {
    this->posXYZ = new float[3]{x, y, z};
}
void Cylinder::setAngle(float alpha) {
    this->angle = alpha;
}
void Cylinder::setAngleNorm(float x, float y, float z) {
    this->angleXYZ = new float[3]{x, y, z};
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
    glColor3f(0, 0, 0);

    glPushMatrix();  //Base black
    glTranslatef(posXYZ[0], posXYZ[1] + 0.01f, posXYZ[2]);
    glRotatef(angle, angleXYZ[0], angleXYZ[1], angleXYZ[2]);
    gluDisk(gluQuadric, 0, section, 10, 1);  //inner = 0 --> No hollow
    glPopMatrix();

    glPushMatrix();  //Walls black
    glTranslatef(posXYZ[0], posXYZ[1], posXYZ[2]);
    glRotatef(angle, angleXYZ[0], angleXYZ[1], angleXYZ[2]);
    gluCylinder(gluQuadric, section, section, length, 200, 200);
    glPopMatrix();

    glPushMatrix();  //Top black
    glTranslatef(posXYZ[0] + length, posXYZ[1], posXYZ[2]);
    glRotatef(angle, angleXYZ[0], angleXYZ[1], angleXYZ[2]);
    gluDisk(gluQuadric, 0, section, 10, 1);
    glPopMatrix();
}
