#include "CGdrive.h"
extern int deltaMove;
extern float angle, deltaAngle, ratio; //绕y轴的旋转角，这个变量允许我们旋转照相机，长宽比
extern float x, y, z; //相机的初始坐标
extern float lx, ly, lz;  //物体相对相机的方向
extern bool MoveFirst;
extern bool MouseState[3];
extern bool OrientState[4];
extern bool isFit, isPan, isMove, rtn, rtnFit;
extern float v;//velocity

void changeSize(int w, int h);
void orientMe(float ang);
void moveMeFlat(int direction);
void updateCamera();
void initZoomPara(int objx, int objy, int objz, float obj_length);
void initPanPara(float posX, float posY, float posZ);
void ViewMove(float valuex, float valuey);
void zoomToFit();
void pan();
void CameraJump(boolean t);