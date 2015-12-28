#include "CGdrive.h"

float angle = 0.0, deltaAngle = 0.0, ratio; //绕y轴的旋转角，这个变量允许我们旋转照相机，长宽比
float x = 0.0f, y = 1.75f, z = 5.0f; //相机的初始坐标
float lx = 0.0f, ly = 0.0f, lz = -1.0f;  //物体相对相机的方向
int deltaMove = 0;

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
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
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
		0.0f, 1.0f, 0.0f);
}
