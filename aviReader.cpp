#include"aviReader.h"
#include "CGdrive.h"

//GLsizei TEXW = 128, TEXH = 128;
uchar * mytex;
CvCapture* capture;
int videotext;

void initAvi(char *videofile){//��ʼ����Ƶ
	capture = cvCaptureFromAVI(videofile);//argv[1]
	if (!capture) return;
	videotext = textpoint++;
	glActiveTexture(GL_TEXTURE0 + videotext);
	glBindTexture(GL_TEXTURE_2D, textureObjects[videotext]);
	//int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);//��ȡԭ��Ƶfps
}

void videoTexInit(){//��mytex�������ݰ󶨵�����
	int texw = 256; int texh = 256;
	//glGenTextures(2, texture);                                         // ���������б�

	genMytex(texw, texh);//�����ҵ�����ͼ	
	glActiveTexture(GL_TEXTURE0 + videotext);
	glBindTexture(GL_TEXTURE_2D, textureObjects[videotext]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texw, texw, 0, GL_RGB, GL_UNSIGNED_BYTE, mytex);
}
void genMytex(int texw, int texh){//����Ƶ֡��������������mytex
	IplImage* frame = cvQueryFrame(capture);	//����Ƶ�в�׽��һ֡ͼ��
	if (!frame) {
		cvReleaseCapture(&capture);
		return;
	}
	IplImage* newframe = cvCreateImage(cvSize(texw, texh), IPL_DEPTH_8U, 3);//��ͼ��Ĵ�С�ȶ�������Ϣ
	cvResize(frame, newframe, CV_INTER_LINEAR);//��frame��ͼ�����õ�newframe��С�������Բ�ֵ�ķ�ʽ���д���
	mytex = (uchar *)newframe->imageData;
	//cvReleaseImage(&frame);
	//cvReleaseImage(&newframe);
}
void getFPS()//��ʱû��
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