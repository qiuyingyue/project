#include "CGdrive.h"
extern int deltaMove;
extern float angle, deltaAngle, ratio; //��y�����ת�ǣ������������������ת������������
extern float x, y, z; //����ĳ�ʼ����
extern float lx, ly, lz;  //�����������ķ���
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