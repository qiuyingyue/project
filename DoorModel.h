
#ifndef DoorModel_hpp
#define DoorModel_hpp

#include <stdio.h>
#include "ObjModel.h"

class DoorModel: public ObjModel {
private:
    bool state = 0; //0->close 1->open
    GLfloat  angle = 0.0f;  //current angle, 0->close, 90->open
    GLfloat speed = 0.5f;
public:
    bool isOpen(){
        return state;
    }
    void open(){
        state = 1;
    }
    void close(){
        state = 0;
    }
    void draw();
};

#endif /* DoorModel_hpp */
