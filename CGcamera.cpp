#include "CGcamera.h"
#include "CGevent.h"
using namespace std;
#define PI 3.14159
#define YZ 1.75
float v=0;//velocity
float angle = 0.0, deltaAngle = 0.0, ratio; //绕y轴的旋转角，这个变量允许我们旋转照相机，长宽比
float x = 2.5f*wallunit, y = YZ, z = 6.0f*wallunit; //相机的初始坐标
float upx = 0.0f, upy = 1.0f, upz = 0.0f; //相机的初始up向量
float lx = 0.0f, ly = 0.0f, lz = 1.0f;  //物体相对相机的方向
float fovy = 45, startFovy, endFovy, prevFovy = 45;
float prevlx, prevly, prevlz; //for return zoomtofit
int deltaMove = 0;
bool isMove = false, isFit = false, isPan = false, rtn = false, rtnFit = false;
float movex, movey, movez, moveDeltax, moveDeltay, moveDeltaz; //相机位置移动的起止点
float fovyChange;
int movecount = 0;
int sumcount = 100;
float R = 1.0, sita = 0, phase = 0;
bool MoveFirst = false;
bool MouseState[3];
bool OrientState[4];

float prev_x, prev_y, prev_z;
float prev_lx, prev_ly, prev_lz;
int row = 19, col = 14;
bool objExist[19][14] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
};

bool bindDetect(int x, int y){
	if (x >= 0 && x < row && y >= 0 && y < col)
		return true;
	return false;
}

bool collision_detection(float srcx, float srcy, float objx, float objy){

	float srcx_convert, srcy_convert, objx_convert, objy_convert;
	//convert x y to the array
	srcx_convert = srcx / wallunit - 1; srcy_convert = srcy / wallunit - 1;
	objx_convert = objx / wallunit - 1; objy_convert = objy / wallunit - 1;
	//cout << srcx_convert << " " << srcy_convert << " " << objx_convert << " " << objy_convert << endl;
	float k;
	if (int(objy_convert + 0.5) == (int)(srcy_convert + 0.5)){
		int startx = (int)(srcx_convert + 0.5), endx = (int)(objx_convert + 0.5);
		int k = (endx - startx) >= 0 ? 1 : -1;
		int number = k * (endx - startx);
		//cout << number << " " << (int)(srcx_convert + 0.5) << " " << startx + k * number<< endl;
		while (number > 0){
			if (bindDetect(startx + k * number, (int)(srcy_convert + 0.5))){
				if (objExist[startx + k * number][(int)(srcy_convert + 0.5)]){
					return true;
				}
			}
			else{
				//cout << "excess bind" << endl;
				return false;
			}
			number--;
		}
	}
	else if (int(objx_convert + 0.5) == int(srcx_convert + 0.5)){
		//cout << "x xiangtong" << endl;
		int starty = (int)(srcy_convert + 0.5), endy = (int)(objy_convert + 0.5);
		int k = (endy - starty) >= 0 ? 1 : -1;
		int number = k * (endy - starty);
		//cout << number << " " << (int)(srcx_convert + 0.5) << " " << starty + k * number<< endl;
		while (number > 0){
			if (bindDetect((int)(srcx_convert + 0.5), starty + k * number)){
				if (objExist[(int)(srcx_convert + 0.5)][starty + k * number]){
					return true;
				}
			}
			else{
				//cout << "excess bind" << endl;
				return false;
			}
			number--;
		}
	}
	else{
		float k = (objy_convert - srcy_convert) / (objx_convert - srcx_convert);
		int startx = (int)(srcx_convert + 0.5), endx = (int)(objx_convert + 0.5);
		int starty = (int)(srcy_convert + 0.5), endy = (int)(objy_convert + 0.5);
		int kx = (endx - startx) >= 0 ? 1 : -1;
		int ky = (endy - starty) >= 0 ? 1 : -1;
		int currentx, currenty;

		int numberx = abs(endx - startx), numbery = abs(endy - starty);
		if (k <= 1){			
			for (int i = 1; i <= numberx; i++){
				currentx = startx + i * kx;
				int currenty = (int)(k * (currentx - srcx_convert) + srcy_convert + 0.5);
				if (bindDetect(currentx, currenty)){
					if (objExist[currentx][currenty]){
						return false;
					}
				}
				else{
					//cout << "excess bind!!" << endl;
					return false;
				}
			}
		}
		else{
			k = (objx_convert - srcx_convert) / (objy_convert - srcy_convert);
			for (int i = 1; i <= numbery; i++){
				currenty = starty + i * ky;
				int currentx = (int)(k * (currenty - srcy_convert) + srcx_convert + 0.5);
				if (bindDetect(currentx, currenty)){
					if (objExist[currentx][currenty]){
						return false;
					}
				}
				else{
					//cout << "excess bind!!" << endl;
					return false;
				}
			}
		}
	}

	return false;
}

void zoom(int a){
	if (a == 1){
		fovy += 1;
	}
	else fovy -= 1;
}
float interpolation(float start, float end, int count, int sum){
	float a;
	a = start + (end - start) * count * 1.0 / sum;
	return a;
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
			lx = centerx - moveCenterx * (sumcount - movecount) - x;
			ly = centery - moveCentery * (sumcount - movecount) - y;
			lz = centerz - moveCenterz * (sumcount - movecount) - z;

			movecount++;
			if (movecount == sumcount) panFinishFit = true;
		}
		else{
			theta += 0.01;
			x = dist * cos(theta) + centerx;
			z = dist * sin(theta) + centerz;
			lx = centerx - x; ly = centery - y; lz = centerz - z;
		}
	}
}

void initZoomPara(int objx, int objy, int objz, float obj_length){
	if (isMove == false){
		movex = objx - x; movey = objy - y;  movez = objz - z;

		//normalize
		float dist = sqrt(lx * lx + ly * ly + lz * lz);
		float lx1 = lx / dist, ly1 = ly / dist, lz1 = lz / dist;
		lx = lx1; ly = ly1; lz = lz1;
		float dist2 = sqrt(movex * movex + movey * movey + movez * movez);
		float movex1 = movex / dist2, movey1 = movey / dist2, movez1 = movez / dist2;

		//这里有一个算改变的fovy的函数
		float objLength = 10; //目标物体长度，相对于相机
		float setFovy = atan2(objLength / 2, dist2) * 180 / PI; //目标fovy
		fovyChange = setFovy - fovy;

		moveDeltax = movex1 - lx1;
		moveDeltay = movey1 - ly1;
		moveDeltaz = movez1 = lz1;
		sumcount = 100;
		moveDeltax /= sumcount;
		moveDeltay /= sumcount;
		moveDeltaz /= sumcount;
		fovyChange /= sumcount;

		movecount = 0;
		isMove = true;

		prevFovy = fovy;
		prevlx = lx; prevly = ly; prevlz = lz;
		rtn = true;
	}
}

void zoomToFit(){
	
	if (isMove && movecount < sumcount && isFit){
		//cout << "movedelata:" << moveDeltax << " " << moveDeltay << " " << moveDeltaz << endl;
		//cout << "lxyz:" << lx << " " << ly << " " << lz << endl;
		lx += moveDeltax;
		ly += moveDeltay;
		lz += moveDeltaz;
		fovy += fovyChange;
		movecount++;


	}
	else if (isMove == true && isFit && movecount == sumcount){
		rtn = true;
		isMove = false;
		isFit = false;
		movecount = 0;
	}

}


void CameraMove(){
	
	float para = 0.1;
	if (OrientState[0] == true) //left
	{
		x += lz * para; 
		z -= lx * para;
	}
	if (OrientState[1] == true) //right
	{
		x -= lz * para;
		z += lx * para;
	}
	if (OrientState[2] == true) //front
	{
		x += lx * para;
		z += lz * para;
	}
	if (OrientState[3] == true) //back
	{
		x -= lx * para;
		z -= lz * para;
	}
}

void ViewMove(float valuex, float valuey){
	sita += valuex / 2;
	phase += valuey / 2;
	//cout << "valuex:" << valuex << " " << "  valuey:" << valuey << endl;
	//cout << "After:   sita:" << sita * 180 / PI << "  phase:" << phase * 180 / PI << endl;
	ly = -sin(phase);
	lx = -sin(sita);
	lz = cos(sita);

}

void CameraJump(){
	boolean t = bindDetect(x/wallunit, z/wallunit);
	boolean t2 = (y > 0 && y < CUBE_HEIGHT*wallunit);
	if (t&&t2){
		y += v;
		if (y >= (CUBE_HEIGHT-1)*wallunit){
			v = 0;
			y = (CUBE_HEIGHT - 1)*wallunit;
		}
		if (y>YZ)
			v -= 0.001;
		else
			v = 0;
	}
	else{
		if (!t){
			y += v;
			if (y > YZ - 5)
				v -= 0.001;
			else
				v = 0;//v = 0.06;
		}
		else if (y>CUBE_HEIGHT*wallunit){
			y += v;
			if (y>(CUBE_HEIGHT+1)*wallunit)
				v -= 0.001;
			else{
				v = 0;
				y = (CUBE_HEIGHT + 1)*wallunit;
			}
		}
		else if (y < 0){
			y += v;
			if (y >= -wallunit){
				y = -wallunit;
				v = 0;
			}
			if (y>YZ - 5)
				v -= 0.001;
			else
				v = 0.0;// 0.06;
		}
	}

}
void updateCamera(){
	prev_x = x; prev_y = y; prev_z = z;
	prev_lx = lx; prev_ly = ly; prev_lz = lz;
	if (isFit){
		zoomToFit();
	}
	if (isPan){
		pan();
	}
	CameraMove();
	CameraJump();
	if (rtnFit){
		lx = prevlx;
		ly = prevly;
		lz = prevlz;
		fovy = prevFovy;
		rtnFit = false;
	}
	//cout << "After: lx" << lx << " " << ly << " " << lz << endl;
	if(collision_detection(prev_x, prev_z, x, z)){
		x = prev_x; y = prev_y; z = prev_z;
		lx = prev_lx; ly = prev_ly; lz = prev_lz;
	}
	//cout << prev_x << " " << prev_y << " " << x << " " << y << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		upx, upy, upz);
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
	gluPerspective(fovy, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		upx, upy, upz);
}



/*
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



*/