extern int deltaMove;
extern float angle, deltaAngle, ratio; //绕y轴的旋转角，这个变量允许我们旋转照相机，长宽比
extern float x, y, z; //相机的初始坐标
extern float lx, ly, lz;  //物体相对相机的方向

void changeSize(int w, int h);
void orientMe(float ang);
void moveMeFlat(int direction);
void pressKey(int key, int x, int y);
void releaseKey(int key, int x, int y);
