#include"CGdrive.h"
#include"CGevent.h"
#include"CGcamera.h"
#define BUFSIZE 512


int mouse_x, mouse_y;
float windowWidth = 640, windowHeight = 360;
bool door_open = false;

void pressKey(unsigned char key, int x, int y){
	switch (key) {
	case 'a'://GLUT_KEY_LEFT:
		OrientState[0] = true; break;
	case 'd'://GLUT_KEY_RIGHT:
		OrientState[1] = true; break;
	case 'w'://GLUT_KEY_UP:
		OrientState[2] = true; break;
	case 's'://GLUT_KEY_DOWN:
		OrientState[3] = true; break;
	default:
		printf("%d\n", key);
		break;
	case ' ':
		v = 0.06;//initial velocity
		break;
	case 'u':
		printf("Screen shot saved\n", key);
		SaveScreenShot();
		break;
	case 9:
		//mode = !mode;
		//printf("mode exchange to %d\n", mode);
		break;
	case 'r':
		if (rtn == true){
			rtnFit = true;
			rtn = false;
		}
		break;

	case 'o': //******There should be a function to detect the area where door can be opened!
		door_open = true;
		objExist[12][8] = 0;
		break;
	case 'n':
		bNurb = !bNurb;
		break;
	}
	

}
void releaseKey(unsigned char key, int x, int y){
	switch (key) {
	case 'a'://GLUT_KEY_LEFT:
		OrientState[0] = false; break;
	case 'd'://GLUT_KEY_RIGHT:
		OrientState[1] = false; break;
	case 'w'://GLUT_KEY_UP:
		OrientState[2] = false; break;
	case 's'://GLUT_KEY_DOWN:
		OrientState[3] = false; break;
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

	if (state == GLUT_DOWN && button == 0) //鼠标左键按下
	{
		MouseState[0] = true;
	}
	if (state == GLUT_UP && button == 0)  //鼠标左键抬起
	{
		MouseState[0] = false;
	}
	if (state == GLUT_DOWN && button == 1) //鼠标中键按下
	{
		MouseState[1] = true;
		isFit = true;
		initZoomPara(posX, posY, posZ, 10);
	}
	if (state == GLUT_UP && button == 1)  //鼠标中键抬起
	{
		MouseState[1] = false;
	}
	if (state == GLUT_DOWN && button == 2) //鼠标右键按下
	{
		MouseState[2] = true;
		if (!isMove){
			isPan = true;
			initPanPara(posX, posY, posZ);
		}
		else{
			isMove = false;
		}
	}
	if (state == GLUT_UP && button == 2)  //鼠标右键抬起
	{
		MouseState[2] = false;
	}

	mouse_x = mousex;
	mouse_y = mousey;
	//cout << "lalala " << mouse_x << " " << mouse_y << endl;
}
void mouseMove(int x, int y){
	float para_x = 1, para_y = 2.7;
	if (MouseState[0] == true){
		MoveFirst = true;
		//std::cout << x << " " << mouse_x << " " << y << " " << mouse_y << std::endl;
		ViewMove((x - mouse_x) * para_x / windowWidth, (y - mouse_y) * para_y / windowHeight);
		mouse_x = x;
		mouse_y = y;
	}
}

//SaveScreenShot  
//保存窗口客户端的截图  
//窗口大小800 * 600  
//截屏、鼠标拾取
void SaveScreenShot()
{
	int clnWidth, clnHeight; //client width and height  
	static void * screenData;
	RECT rc;
	int len = 800 * 600 * 3;
	screenData = malloc(len);
	memset(screenData, 0, len);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, screenData);

	//生成文件名字符串，以时间命名  
	time_t tm = 0;
	tm = time(NULL);
	char lpstrFilename[256] = { 0 };
	sprintf_s(lpstrFilename, sizeof(lpstrFilename), "截屏%d.bmp", tm);

	WriteBitmapFile(lpstrFilename, 800, 600, (unsigned char*)screenData);
	//释放内存  
	free(screenData);

}

//WriteBitmapFile  
//根据bitmapData的（RGB）数据，保存bitmap  
//filename是要保存到物理硬盘的文件名（包括路径）  
BOOL WriteBitmapFile(char * filename, int width, int height, unsigned char * bitmapData)
{
	//填充BITMAPFILEHEADER  
	BITMAPFILEHEADER bitmapFileHeader;
	memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
	bitmapFileHeader.bfType = 0x4d42;   //BM  
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//填充BITMAPINFOHEADER  
	BITMAPINFOHEADER bitmapInfoHeader;
	memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = width * abs(height) * 3;

	//////////////////////////////////////////////////////////////////////////  
	FILE * filePtr;         //连接要保存的bitmap文件用  
	unsigned char tempRGB;  //临时色素  
	int imageIdx;

	//交换R、B的像素位置,bitmap的文件放置的是BGR,内存的是RGB  
	for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapData[imageIdx];
		bitmapData[imageIdx] = bitmapData[imageIdx + 2];
		bitmapData[imageIdx + 2] = tempRGB;
	}

	filePtr = fopen(filename, "wb");
	if (NULL == filePtr)
	{
		return FALSE;
	}

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);

	fclose(filePtr);
	return TRUE;
}
void mousePick(int button, int state, int x, int y)
{
	//if (mode) return;
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//std::cout << x << " " << y << std::endl;
		glSelectBuffer(BUFSIZE, selectBuf);//设置选择缓冲区
		glRenderMode(GL_SELECT);//进入选择模式selection mode
		glMatrixMode(GL_PROJECTION);// 保存投影矩阵
		glPushMatrix();
		glLoadIdentity();
		glGetIntegerv(GL_VIEWPORT, viewport);
		/*  create 1x1 pixel picking region near cursor location */
		gluPickMatrix(x, (viewport[3] - y), 1.0, 1.0, viewport);//设置画框近平面大小
		
		gluPerspective(45, 640.0/ 360, 1, 1000);
		/*上面的代码中在执行gluPickMatrix值钱先保存了投影矩阵，然后再重新创造一个新的供自己使用。
		原因是gluPickMatrix会操作投影举证，该函数和后续的gluPerspective共同作用，最终会生成一个全新的投影矩阵，该矩阵中的所有物体，
		都会被视为选中。为了不影响旧有的投影矩阵，因此需要保存先*/

		glMatrixMode(GL_MODELVIEW);
		glInitNames();
		glPushName(0);
	//绘制
		//drawSnowmen(GL_SELECT);
		stopPicking(selectBuf);
	}
	return;
}

void stopPicking(GLuint buffer[]) {

	int hits;

	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);//得到选中物体的数目
	// if there are hits process them
	processHits(hits, buffer);
}
void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr, minZ, *ptrNames, numberOfNames;

	printf("number of hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	minZ = 0xffffffff;
	ptrNames = NULL;
	for (i = 0; i < hits; i++) {
		names = *ptr;
		printf(" number of names for hit = %d\n", names); ptr++;
		  printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
		  printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;
		  printf("   the name is ");
		  for (j = 0; j < names; j++) {
		         printf("%d ", *ptr); ptr++;
		
		}
	      printf("\n");

		/*ptr++;
		if (*ptr < minZ) {
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr + 2;
		}
		ptr += names + 2;
	}
	if (hits>0)
	{
		printf("The closest hit names are ");
		ptr = ptrNames;
		for (j = 0; j < numberOfNames; j++, ptr++) {
			printf("%d ", *ptr);
			//处理拾取物体的事件
			//color[*ptr] = 1 - color[*ptr];
		}
		printf("\n");*/
	}
}