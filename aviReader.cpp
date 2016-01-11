#include"aviReader.h"
#include "CGdrive.h"

//GLsizei TEXW = 128, TEXH = 128;
uchar * mytex;
CvCapture* capture;
int videotext;

void initAvi(char *videofile){//初始化视频
	capture = cvCaptureFromAVI(videofile);//argv[1]
	if (!capture) return;
	videotext = textpoint++;
	glActiveTexture(GL_TEXTURE0 + videotext);
	glBindTexture(GL_TEXTURE_2D, textureObjects[videotext]);
	//int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);//获取原视频fps
}

void videoTexInit(){//将mytex像素数据绑定到纹理
	int texw = 256; int texh = 256;
	//glGenTextures(2, texture);                                         // 生成纹理列表

	genMytex(texw, texh);//产生我的纹理图	
	glActiveTexture(GL_TEXTURE0 + videotext);
	glBindTexture(GL_TEXTURE_2D, textureObjects[videotext]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texw, texw, 0, GL_RGB, GL_UNSIGNED_BYTE, mytex);
}
void genMytex(int texw, int texh){//将视频帧的像素数据贴到mytex
	IplImage* frame = cvQueryFrame(capture);	//从视频中捕捉的一帧图像
	if (!frame) {
		cvReleaseCapture(&capture);
		return;
	}
	IplImage* newframe = cvCreateImage(cvSize(texw, texh), IPL_DEPTH_8U, 3);//对图像的大小等定义框架信息
	cvResize(frame, newframe, CV_INTER_LINEAR);//将frame的图像设置到newframe大小，用线性插值的方式进行处理
	mytex = (uchar *)newframe->imageData;
	//cvReleaseImage(&frame);
	//cvReleaseImage(&newframe);
}
void getFPS()//暂时没用
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		printf(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	
}