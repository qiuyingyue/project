#include "CGdrive.h"
using namespace std;

float angle = 0.0, deltaAngle = 0.0, ratio; //绕y轴的旋转角，这个变量允许我们旋转照相机，长宽比
float x = 0.0f, y = 1.75f, z = 5.0f; //相机的初始坐标
float upx = 0.0f, upy = 1.0f, upz = 0.0f; //相机的初始up向量
float lx = 0.0f, ly = 0.0f, lz = -1.0f;  //物体相对相机的方向
int deltaMove = 0;
bool isMove = false, isFit = false, isPan = false;
float movex, movey, movez, moveDeltax, moveDeltay, moveDeltaz; //相机位置移动的起止点
int movecount = 0;
int sumcount = 100;

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	y = y + direction*(ly)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}

void initZoomPara(int objx, int objy, int objz){
	if (isMove == false){
		movex = objx - x; movey = objy - y;  movez = objz - z;

		//normalize
		float dist = sqrt(lx * lx + ly * ly + lz * lz);
		float lx1 = lx / dist, ly1 = ly / dist, lz1 = lz / dist;
		float dist2 = sqrt(movex * movex + movey * movey + movez * movez);
		float movex1 = movex / dist2, movey1 = movey / dist2, movez1 = movez / dist2;

		moveDeltax = movex1 - lx1;
		moveDeltay = movey1 - ly1;
		moveDeltaz = movez1 = lz1;
		sumcount = 1000;
		moveDeltax /= sumcount;
		moveDeltay /= sumcount;
		moveDeltaz /= sumcount;
		movex /= sumcount;
		movey /= sumcount;
		movez /= sumcount;
		movecount = 0;
		isMove = true;
		//cout << movex << " " << movey << " " << movez << endl;
		//cout << moveDeltax << " " << moveDeltay << " " << moveDeltaz << endl;
	}
}

void zoomToFit(){

	if (isMove && movecount < sumcount && isFit){
		x += movex;
		y += movey;
		z += movez;
		lx += moveDeltax;
		ly += moveDeltay;
		lz += moveDeltaz;
		movecount++;
		glLoadIdentity();
		gluLookAt(x, y, z,
			x + lx, y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
	}
	else if (isMove == true && isFit && movecount == sumcount){
		isMove = false;
		isFit = false;
		movecount = 0;
	}

}

float theta, dist, centerx, centery, centerz, moveCenterx, moveCentery, moveCenterz;
bool panFinishFit = false;
void initPanPara(float posX, float posY, float posZ){
	if (isMove == false){
		centerx = posX;
		centery = posY;
		centerz = posZ;

		sumcount = 1000;
		movecount = 0;
		moveCenterx = (centerx - (x + lx)) / sumcount;
		moveCentery = (centery - (y + ly)) / sumcount;
		moveCenterz = (centerz - (z + lz)) / sumcount;

		float deltax = x - centerx, deltay = y - centery, deltaz = z - centerz;
		dist = sqrt(deltax * deltax + deltay * deltay + deltaz * deltaz);
		theta = atan2(deltaz, deltax);
		isMove = true;
		panFinishFit = false;
	}
}

void pan(){

	if (isPan && isMove){
		if (!panFinishFit){
			glLoadIdentity();
			gluLookAt(x, y, z,
				centerx - moveCenterx * (sumcount - movecount),
				centery - moveCentery * (sumcount - movecount),
				centerz - moveCenterz * (sumcount - movecount),
				0.0f, 1.0f, 0.0f);
			movecount++;
			if (movecount == sumcount) panFinishFit = true;
		}
		else{
			theta += 0.01;
			x = dist * cos(theta) + centerx;
			z = dist * sin(theta) + centerz;
			glLoadIdentity();
			gluLookAt(x, y, z,
				centerx, centery, centerz,
				0.0f, 1.0f, 0.0f);
		}
	}
}

void mouseClick(int button, int state, int mousex, int mousey){
	GLfloat winX, winY, winZ;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)mousex;
	winY = viewport[3] - (float)mousey;
	glReadPixels(int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	//读取一些像素。当前可以简单理解为“把已经绘制好的像素（它可能已经被保存到显卡的显存中）读取到内存”。
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	//gluProject的逆 

	cout << winX << " " << winY << " " << winZ << endl;
	cout << posX << " " << posY << " " << posZ << endl;

	if (state == GLUT_DOWN && button == 0) //鼠标左键按下
	{
		if (posZ > -200){
			float deltax = posX - x, deltay = posY - y, deltaz = posZ - z;
			float dist_temp = sqrt(deltax * deltax + deltay * deltay + deltaz * deltaz);
			deltax /= dist_temp; deltay /= dist_temp; deltaz /= dist_temp;
			float dist_eye_obj = 2;
			float objx = posX - deltax * dist_eye_obj, objy = posY - deltay * dist_eye_obj, objz = posZ - deltaz * dist_eye_obj;
			isFit = true;
			initZoomPara(objx, objy, objz);
		}
	}
	if (state == GLUT_DOWN && button == 2) //鼠标右键按下
	{
		if (posZ > -100){
			//这里需要先缓慢把目标移到中心

			isPan = true;
			initPanPara(posX, posY, posZ);

		}
	}
	if (state == GLUT_UP && button == 2) //鼠标右键抬起
	{
		isPan = false;
		isMove = false;
	}
}

void mouseMove(int x, int y){

}

void pressKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.01f; break;
	case GLUT_KEY_UP:
		deltaMove = 1; break;
	case GLUT_KEY_DOWN:
		deltaMove = -1; break;
	}
}


void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		deltaMove = 0; break;
	}
}


void changeSize(int w, int h)
{
	// 防止被0除.
	if (h == 0)
		h = 1;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//设置视口为整个窗口大小
	glViewport(0, 0, w, h);
	//设置可视空间
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		upx, upy, upz);
}
