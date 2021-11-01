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
    void setInitAngle(float, float[3]);
    void addRotationY(int);
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
void Cylinder::setInitAngle(float alpha, float angleNorm[3]) {
    this->angle = alpha;
    this->angelNorm = angleNorm;
}

void Cylinder::addRotationY(int rotation) {
    this->rotation = rotation;
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
    glTranslatef(coordinates[0], coordinates[1] + 0.01f, coordinates[2]);
    glRotatef(angle, angelNorm[0], angelNorm[1], angelNorm[2]);
    glRotatef(rotation, 0, 0, 1);
    gluDisk(gluQuadric, 0, section, 10, 1);  //inner = 0 --> No hollow
    glPopMatrix();

    glPushMatrix();  //Walls black
    glTranslatef(coordinates[0], coordinates[1], coordinates[2]);
    glRotatef(angle, angelNorm[0], angelNorm[1], angelNorm[2]);
    glRotatef(rotation, 0, 0, 1);
    gluCylinder(gluQuadric, section, section, length, 200, 200);
    glPopMatrix();

    glPushMatrix();  //Top black
    glTranslatef(coordinates[0] + length, coordinates[1], coordinates[2]);
    glRotatef(angle, angelNorm[0], angelNorm[1], angelNorm[2]);
    glRotatef(rotation, 0, 0, 1);
    gluDisk(gluQuadric, 0, section, 10, 1);
    glPopMatrix();
}
