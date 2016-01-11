#include "DoorModel.h"

void DoorModel::draw(){
    if (state == 0){
        if (angle > 0)
            angle -= speed;
        if (angle < 0)
            angle = 0;
    }
    else{
        if (angle < 90)
            angle +=speed;
        if (angle > 90)
            angle = 90;
    }
    glPushMatrix();
    glTranslatef(-0.5, 0, 0);
    glRotated(angle, 0, 1, 0);
    glTranslatef(0.5, 0, 0);
    ObjModel::draw();
    glPopMatrix();
}
