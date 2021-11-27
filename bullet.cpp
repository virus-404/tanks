#include "opengl.h"

using namespace std;
class Board;
class Cylinder;

class Bullet {
   private:
    float x, y;
    char shooter;
    Board *board;

   public:
    Bullet(float, float, char);
    void setBoard(Board*);
    void draw();
};

Bullet::Bullet(float x, float y, char shooter) {
    this->x = x;
    this->y = y;
    this->shooter = shooter;
}

void Bullet::setBoard(Board *board){
    this->board = board;
}

void Bullet::draw() {
    glDisable(GL_TEXTURE_2D);
    /*
    Cylinder *cyl = new Cylinder();

    cyl->setLength(2);
    cyl->setSection(1);
    cyl->setCoordinates(
        15.00f * DISTANCE_SUB_UNIT - CENTER_SUB_UNIT,
        8.00f * DISTANCE_SUB_UNIT - CENTER_SUB_UNIT,
        10.0f);
    cyl->setOrientation(90.0f, new float[3]{0.0f, 1.0f, 0.0f});

    cyl->draw();
    delete cyl;
    */
    glEnable(GL_TEXTURE_2D);
}